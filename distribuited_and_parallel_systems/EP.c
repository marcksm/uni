/* Lucas Seiki Oshiro             - 9298228
   Marcos Vinicius do Carmo Sousa - 9298274
   Matheus Tavares Bernardino     - 9292987 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <omp.h>

#define DOISPI 6.28318530718
#define pulacomentario(f, c) \
    while ((c = getc (f)) == '#') while ((c = getc (f)) != '\n'); \
    ungetc (c, f)

typedef char *string;
double *img;
int w, h;

void ler (string nome) {
    FILE *f = fopen (nome, "r");
    int tipo;
    int size;
    char c;
    int i;

    (void) fscanf (f, "%c %d", &c, &tipo);
    while (getc (f) != '\n');

    pulacomentario (f, c);
    (void) fscanf (f, "%d %d %d", &w, &h, &i);
    while (getc (f) != '\n');

    size = 3 * w * h;

    img = malloc (size * sizeof (double));

    if (tipo == 3) {
        int i, tmp[3];
        double *p = img;
        for (i = 0; i < size; i += 3) {
            (void) fscanf (f, "%d %d %d", &(tmp[0]), &(tmp[1]), &(tmp[2]));
            *(p++) = (double) tmp[0] / 256.0;
            *(p++) = (double) tmp[1] / 256.0;
            *(p++) = (double) tmp[2] / 256.0;
        }
    }
    else {
        uint8_t *tmp = malloc (size * sizeof (uint8_t));
        (void) fread (tmp, sizeof (uint8_t), size, f);

        #pragma omp parallel for
        for (i = 0; i < size; i += 3) {
            img[i] = tmp[i] / 256.0;
            img[i + 1] = tmp[i + 1] / 256.0;
            img[i + 2] = tmp[i + 2] / 256.0;
        }
        free (tmp);
    }

    fclose (f);
}

void imprime (string nome) {
    FILE *f = fopen (nome, "w");
    int i;
    fprintf (f, "P3\n");
    fprintf (f, "%d %d\n", w, h);
    fprintf (f, "255\n");

    for (i = 0; i < 3 * h * w; i++) {
        fprintf (f, "%d ", (int) round (img[i] * 256.0));
    }

    fclose (f);
}

/*__m512d _mm512_abs_pd (__m512d v2) */
void transforma (int iN, int pN) {
    int lim;
    int i;
    int q, g, k;
    int j;
    double c, s, Rx, Ry, Bx, By;
    double *deltaB, *deltaR, delta;
    int deltasize = w * h * sizeof (double);
    deltaR = malloc (w * h, sizeof (double));
    deltaB = malloc (w * h, sizeof (double));

    for (i = 0; i < iN; i++) {

        memset (deltaR, 0, deltasize);
        memset (deltaB, 0, deltasize);

        for (q = 2; q < h - 2; q++) {
            for (g = 2; g < w - 2; g++) {
                k = (q * w + g);
                j = k * 3;
                s = sin (DOISPI * img[j+1]);
                c = cos (DOISPI * img[j+1]);
                Rx = s * img[j];
                Ry = c * img[j];

                Bx = -s * img[j+2];
                By = -c * img[j+2];

                if (Rx > 0) {
                    delta = ((1 - img[j+3]) * Rx) / 4;
                    deltaR[k] -= delta;
                    deltaR[k+1] += delta;
                }
                else if (Rx < 0) {
                    delta = ((1 - img[j-3]) * Rx) / 4;
                    deltaR[k] += delta;
                    deltaR[k-1] -= delta;
                }

                if (Ry > 0) {
                    delta = ((1 - img[j - 3*w]) * Ry) / 4;
                    deltaR[k] -= delta;
                    deltaR[k - w] += delta;
                }
                else if (Ry < 0) {
                    delta = ((1 - img[j + 3*w]) * Ry) / 4;
                    deltaR[k] += delta;
                    deltaR[k + w] -= delta;
                }

                if (Bx > 0) {
                    delta = ((1 - img[j+5]) * Bx) / 4;
                    deltaB[k] -= delta;
                    deltaB[k+1] += delta;
                }
                else if (Bx < 0) {
                    delta = ((1 - img[j - 1]) * Bx) / 4;
                    deltaB[k] += delta;
                    deltaB[k-1] -= delta;
                }

                if (By > 0) {
                    delta = ((1 - img[j - 3*w + 2]) * By) / 4;
                    deltaB[k] -= delta;
                    deltaB[k - w] += delta;
                }
                else if (By < 0) {
                    delta = ((1 - img[j + 3*w + 2]) * By) / 4;
                    deltaB[k] += delta;
                    deltaB[k + w] -= delta;
                }

            }
        }

        /*Borda interna superior*/
        lim = 2*w - 2;
        for (k = 2 + w; k < lim; k++) {
            j = k * 3;
            s = sin (DOISPI * img[j+1]);
            c = cos (DOISPI * img[j+1]);
            Rx = s * img[j];
            Ry = c * img[j];

            Bx = -s * img[j+2];
            By = -c * img[j+2];

            /*dir e esq*/
            if (Rx > 0) {
                delta = ((1 - img[j+3]) * Rx) / 4;
                deltaR[k] -= delta;
                deltaR[k+1] += delta;
            }
            else if (Rx < 0) {
                delta = ((1 - img[j-3]) * Rx) / 4;
                deltaR[k] += delta;
                deltaR[k-1] -= delta;
            }

            /*baixo*/
            if (Ry < 0){
                delta = ((1 - img[j + 3*w]) * Ry) / 4;
                deltaR[k] += delta;
                deltaR[k + w] -= delta;
            }

            /*dir e esq*/
            if (Bx > 0) {
                delta = ((1 - img[j+5]) * Bx) / 4;
                deltaB[k] -= delta;
                deltaB[k+1] += delta;
            }
            else if (Bx < 0) {
                delta = ((1 - img[j - 1]) * Bx) / 4;
                deltaB[k] += delta;
                deltaB[k-1] -= delta;
            }

            /*baixo*/
            if (By < 0) {
                delta = ((1 - img[j + 3*w + 2]) * By) / 4;
                deltaB[k] += delta;
                deltaB[k + w] -= delta;
            }
        }

        /*Borda interna inferior*/
        lim = w*(1 + h - 2) - 2;
        for (k = 2 + w*(h-2); k < lim; k++) {
            j = k * 3;
            s = sin (DOISPI * img[j+1]);
            c = cos (DOISPI * img[j+1]);
            Rx = s * img[j];
            Ry = c * img[j];

            Bx = -s * img[j+2];
            By = -c * img[j+2];

            /*dir e esq*/
            if (Rx > 0) {
                delta = ((1 - img[j+3]) * Rx) / 4;
                deltaR[k] -= delta;
                deltaR[k+1] += delta;
            }
            else if (Rx < 0) {
                delta = ((1 - img[j-3]) * Rx) / 4;
                deltaR[k] += delta;
                deltaR[k-1] -= delta;
            }

            /*cima*/
            if (Ry > 0) {
                delta = ((1 - img[j - 3*w]) * Ry) / 4;
                deltaR[k] -= delta;
                deltaR[k - w] += delta;
            }

            /*dir e esq*/
            if (Bx > 0) {
                delta = ((1 - img[j+5]) * Bx) / 4;
                deltaB[k] -= delta;
                deltaB[k+1] += delta;
            }
            else if (Bx < 0) {
                delta = ((1 - img[j - 1]) * Bx) / 4;
                deltaB[k] += delta;
                deltaB[k-1] -= delta;
            }

            /*cima*/
            if (By > 0) {
                delta = ((1 - img[j - 3*w + 2]) * By) / 4;
                deltaB[k] -= delta;
                deltaB[k - w] += delta;
            }
        }

        /*Borda interna esquerda*/
        lim = (h - 2) * w + 1;
        for (k = 2*w + 1; k < lim; k += w) {
            j = k * 3;
            s = sin (DOISPI * img[j+1]);
            c = cos (DOISPI * img[j+1]);
            Rx = s * img[j];
            Ry = c * img[j];

            Bx = -s * img[j+2];
            By = -c * img[j+2];

            /*dir*/
            if (Rx > 0) {
                delta = ((1 - img[j+3]) * Rx) / 4;
                deltaR[k] -= delta;
                deltaR[k+1] += delta;
            }

            /*cima e baixo*/
            if (Ry > 0) {
                delta = ((1 - img[j - 3*w]) * Ry) / 4;
                deltaR[k] -= delta;
                deltaR[k - w] += delta;
            }
            else if (Ry < 0) {
                delta = ((1 - img[j + 3*w]) * Ry) / 4;
                deltaR[k] += delta;
                deltaR[k + w] -= delta;
            }


            /*dir*/
            if (Bx > 0) {
                delta = ((1 - img[j+5]) * Bx) / 4;
                deltaB[k] -= delta;
                deltaB[k+1] += delta;
            }

            /*cima e baixo*/
            if (By > 0) {
                delta = ((1 - img[j - 3*w + 2]) * By) / 4;
                deltaB[k] -= delta;
                deltaB[k - w] += delta;
            }
            else if (By < 0) {
                delta = ((1 - img[j + 3*w + 2]) * By) / 4;
                deltaB[k] += delta;
                deltaB[k + w] -= delta;
            }

        }

        /*Borda interna direita*/
        lim = (w - 2) + w * (h - 2);
        for (k = (w - 2) + 2 * w; k < lim; k += w) {
            j = k * 3;
            s = sin (DOISPI * img[j+1]);
            c = cos (DOISPI * img[j+1]);
            Rx = s * img[j];
            Ry = c * img[j];

            Bx = -s * img[j+2];
            By = -c * img[j+2];

            /*esq*/
            if (Rx < 0) {
                delta = ((1 - img[j-3]) * Rx) / 4;
                deltaR[k] += delta;
                deltaR[k-1] -= delta;
            }

            /*cima e baixo*/
            if (Ry > 0) {
                delta = ((1 - img[j - 3*w]) * Ry) / 4;
                deltaR[k] -= delta;
                deltaR[k - w] += delta;
            }
            else if (Ry < 0) {
                delta = ((1 - img[j + 3*w]) * Ry) / 4;
                deltaR[k] += delta;
                deltaR[k + w] -= delta;
            }

            /*esq*/
            if (Bx < 0) {
                delta = ((1 - img[j - 1]) * Bx) / 4;
                deltaB[k] += delta;
                deltaB[k-1] -= delta;
            }

            /*cima e baixo*/
            if (By > 0) {
                delta = ((1 - img[j - 3*w + 2]) * By) / 4;
                deltaB[k] -= delta;
                deltaB[k - w] += delta;
            }
            else if (By < 0) {
                delta = ((1 - img[j + 3*w + 2]) * By) / 4;
                deltaB[k] += delta;
                deltaB[k + w] -= delta;
            }


        }

        /*canto interno superior esquerdo*/
        k = w + 1;
        j = k * 3;
        s = sin (DOISPI * img[j+1]);
        c = cos (DOISPI * img[j+1]);
        Rx = s * img[j];
        Ry = c * img[j];
        Bx = -s * img[j+2];
        By = -c * img[j+2];
        // printf ("Sup-esq: Rx=%f Ry=%f Bx=%f By=%f\n", Rx, Ry, Bx, By);
        if (Rx > 0) {
            delta = ((1 - img[j+3]) * Rx) / 4;
            deltaR[k] -= delta;
            deltaR[k+1] += delta;
        }
        if (Bx > 0) {
            delta = ((1 - img[j+5]) * Bx) / 4;
            deltaB[k] -= delta;
            deltaB[k+1] += delta;
        }
        if (Ry < 0) {
            delta = ((1 - img[j + 3*w]) * Ry) / 4;
            deltaR[k] += delta;
            deltaR[k + w] -= delta;
        }
        if (By < 0) {
            delta = ((1 - img[j + 3*w + 2]) * By) / 4;
            deltaB[k] += delta;
            deltaB[k + w] -= delta;
        }


        /*canto interno superior direito*/
        k = 2 * w - 2;
        j = k * 3;
        s = sin (DOISPI * img[j+1]);
        c = cos (DOISPI * img[j+1]);
        Rx = s * img[j];
        Ry = c * img[j];
        Bx = -s * img[j+2];
        By = -c * img[j+2];
        // printf ("Sup-dir: Rx=%f Ry=%f Bx=%f By=%f\n", Rx, Ry, Bx, By);
        if (Rx < 0) {
            delta = ((1 - img[j-3]) * Rx) / 4;
            deltaR[k] += delta;
            deltaR[k-1] -= delta;
        }
        if (Bx < 0) {
            delta = ((1 - img[j - 1]) * Bx) / 4;
            deltaB[k] += delta;
            deltaB[k-1] -= delta;
        }
        if (Ry < 0) {
            delta = ((1 - img[j + 3*w]) * Ry) / 4;
            deltaR[k] += delta;
            deltaR[k + w] -= delta;
        }
        if (By < 0) {
            delta = ((1 - img[j + 3*w + 2]) * By) / 4;
            deltaB[k] += delta;
            deltaB[k + w] -= delta;
        }

        /*canto interno inferior esquerdo*/
        k = 1 + w * (h - 2);
        j = k * 3;
        s = sin (DOISPI * img[j+1]);
        c = cos (DOISPI * img[j+1]);
        Rx = s * img[j];
        Ry = c * img[j];
        Bx = -s * img[j+2];
        By = -c * img[j+2];
        // printf ("Inf-esq: Rx=%f Ry=%f Bx=%f By=%f\n", Rx, Ry, Bx, By);
        if (Rx > 0) {
            delta = ((1 - img[j+3]) * Rx) / 4;
            deltaR[k] -= delta;
            deltaR[k+1] += delta;
        }
        if (Bx > 0) {
            delta = ((1 - img[j+5]) * Bx) / 4;
            deltaB[k] -= delta;
            deltaB[k+1] += delta;
        }
        if (Ry > 0) {
            delta = ((1 - img[j - 3*w]) * Ry) / 4;
            deltaR[k] -= delta;
            deltaR[k - w] += delta;
        }
        if (By > 0) {
            delta = ((1 - img[j - 3*w + 2]) * By) / 4;
            deltaB[k] -= delta;
            deltaB[k - w] += delta;
        }


        /*canto interno inferior direito*/
        k = (w - 2) +  w * (h - 2);
        j = k * 3;
        s = sin (DOISPI * img[j+1]);
        c = cos (DOISPI * img[j+1]);
        Rx = s * img[j];
        Ry = c * img[j];
        Bx = -s * img[j+2];
        By = -c * img[j+2];
        // printf ("Inf-dir: Rx=%f Ry=%f Bx=%f By=%f\n", Rx, Ry, Bx, By);
        if (Rx < 0) {
            delta = ((1 - img[j-3]) * Rx) / 4;
            deltaR[k] += delta;
            deltaR[k-1] -= delta;
        }
        if (Bx < 0) {
            delta = ((1 - img[j - 1]) * Bx) / 4;
            deltaB[k] += delta;
            deltaB[k-1] -= delta;
        }
        if (Ry > 0) {
            delta = ((1 - img[j - 3*w]) * Ry) / 4;
            deltaR[k] -= delta;
            deltaR[k - w] += delta;
        }
        if (By > 0) {
            delta = ((1 - img[j - 3*w + 2]) * By) / 4;
            // printf ("delta = %f\n", delta);
            deltaB[k] -= delta;
            deltaB[k - w] += delta;
        }

        /*aplicação dos deltas*/
        for (q = 1; q < h - 1; q++)
            for (g = 1; g < w - 1; g++) {
                k = (q * w + g);
                j = 3 * k;
                img[j] += deltaR[k];
                img[j+2] += deltaB[k];
            }


        /*Verificar over e under flow AQUI*/
        for (j = 0; j < w * h * 3; j += 3) {
            if (img[j] > 255.0/256.0) img[j] = 255.0/256.0;
            else if (img[j] < 0) img[j] = 0;
            if (img[j+2] > 255.0/256.0) img[j+2] = 255.0/256.0;
            else if (img[j+2] < 0) img[j+2] = 0;
        }

        /*Correção do G*/
        for (q = 1; q < h - 1; q++)
            for (g = 1; g < w - 1; g++) {
                j = 3 * (q * w + g);
                if (img[j] != 0 || img[j + 2] != 0)
                    img[j + 1] = fmod (DOISPI * img[j + 1] + atan (img[j] / img[j + 2]), DOISPI) / DOISPI;
            }

    }
    free (deltaR);
    free (deltaB);
}

void transformaC (int iN, int pN) {
    int lim;
    int i;
    int k, q, g;
    int j;
    double c, Ry, By;
    double *deltaB, *deltaR, delta;
    deltaR = malloc (w * h, sizeof (double));
    deltaB = malloc (w * h, sizeof (double));

    for (i = 0; i < iN; i++) {
        memset (deltaR, 0, deltasize);
        memset (deltaB, 0, deltasize);

        /*Borda interna*/
        lim = (h - 2) * w + 1;
        for (k = 2*w + 1; k < lim; k += w) {
            j = k * 3;
            c = cos (DOISPI * img[j+1]);
            Ry = c * img[j];
            By = -c * img[j+2];

            /*cima e baixo*/
            if (Ry > 0) {
                delta = ((1 - img[j - 3*w]) * Ry) / 4;
                deltaR[k] -= delta;
                deltaR[k - w] += delta;
            }
            else if (Ry < 0) {
                delta = ((1 - img[j + 3*w]) * Ry) / 4;
                deltaR[k] += delta;
                deltaR[k + w] -= delta;
            }


            /*cima e baixo*/
            if (By > 0) {
                delta = ((1 - img[j - 3*w + 2]) * By) / 4;
                deltaB[k] -= delta;
                deltaB[k - w] += delta;
            }
            else if (By < 0) {
                delta = ((1 - img[j + 3*w + 2]) * By) / 4;
                deltaB[k] += delta;
                deltaB[k + w] -= delta;
            }
        }

        /*canto superior*/
        k = w + 1;
        j = k * 3;
        c = cos (DOISPI * img[j+1]);
        Ry = c * img[j];
        By = -c * img[j+2];
        if (Ry < 0) {
            delta = ((1 - img[j + 3*w]) * Ry) / 4;
            deltaR[k] += delta;
            deltaR[k + w] -= delta;
        }
        if (By < 0) {
            delta = ((1 - img[j + 3*w + 2]) * By) / 4;
            deltaB[k] += delta;
            deltaB[k + w] -= delta;
        }

        /*canto inferior*/
        k = 1 + w * (h - 2);
        j = k * 3;
        c = cos (DOISPI * img[j+1]);
        Ry = c * img[j];
        By = -c * img[j+2];
        if (Ry < 0) {
            delta = ((1 - img[j + 3*w]) * Ry) / 4;
            deltaR[k] += delta;
            deltaR[k + w] -= delta;
        }
        if (By < 0) {
            delta = ((1 - img[j + 3*w + 2]) * By) / 4;
            deltaB[k] += delta;
            deltaB[k + w] -= delta;
        }

        /*aplicação dos deltas*/
        for (q = 1; q < h - 1; q++)
            for (g = 1; g < w - 1; g++) {
                k = (q * w + g);
                j = 3 * k;
                img[j] += deltaR[k];
                img[j+2] += deltaB[k];
            }

        /*Verificar over e under flow AQUI*/
        for (j = 0; j < w * h * 3; j += 3) {
            if (img[j] >= 1) img[j] = 255.0/256.0;
            else if (img[j] < 0) img[j] = 0;
            if (img[j+2] >= 1) img[j+2] = 255.0/256.0;
            else if (img[j+2] < 0) img[j+2] = 0;
        }

        /*Correção do G*/
        for (q = 1; q < h - 1; q++)
            for (g = 1; g < w - 1; g++) {
                j = 3 * (q * w + g);
                if (img[j] != 0 || img[j + 2] != 0)
                    img[j + 1] = fmod (DOISPI * img[j + 1] + atan (img[j] / img[j + 2]), DOISPI) / DOISPI;
            }

    }
    free (deltaB);
    free (deltaR);
}

 void transformaL (int iN, int pN) {
     int lim;
     int i;
     int k, q, g;
     int j;
     double s, Rx, Bx;
     double *deltaB, *deltaR, delta;
     deltaR = malloc (w * h, sizeof (double));
     deltaB = malloc (w * h, sizeof (double));

     for (i = 0; i < iN; i++) {

         /*Borda interna*/
         lim = 2*w - 2;
         for (k = 2 + w; k < lim; k++) {
             j = k * 3;
             s = sin (DOISPI * img[j+1]);
             Rx = s * img[j];
             Bx = -s * img[j+2];

             /*dir e esq*/
             if (Rx > 0) {
                delta = ((1 - img[j+3]) * Rx) / 4;
                deltaR[k] -= delta;
                deltaR[k+1] += delta;
             }
             else if (Rx < 0) {
                 delta = ((1 - img[j-3]) * Rx) / 4;
                 deltaR[k] += delta;
                 deltaR[k-1] -= delta;
             }

             /*dir e esq*/
             if (Bx > 0) {
                 delta = ((1 - img[j+5]) * Bx) / 4;
                 deltaB[k] -= delta;
                 deltaB[k+1] += delta;
             }
             else if (Bx < 0) {
                 delta = ((1 - img[j - 1]) * Bx) / 4;
                 deltaB[k] += delta;
                 deltaB[k-1] -= delta;
             }
         }

         /*canto interno esquerdo*/
         k = w + 1;
         j = k * 3;
         s = sin (DOISPI * img[j+1]);
         Rx = s * img[j];
         Bx = -s * img[j+2];
         if (Rx > 0) {
             delta = ((1 - img[j+3]) * Rx) / 4;
             deltaR[k] -= delta;
             deltaR[k+1] += delta;
         }
         if (Bx > 0) {
             delta = ((1 - img[j+5]) * Bx) / 4;
             deltaB[k] -= delta;
             deltaB[k+1] += delta;
         }

         /*canto interno direito*/
         k = 2 * w - 2;
         j = k * 3;
         s = sin (DOISPI * img[j+1]);
         Rx = s * img[j];
         Bx = -s * img[j+2];
         if (Rx < 0) {
             delta = ((1 - img[j-3]) * Rx) / 4;
             deltaR[k] += delta;
             deltaR[k-1] -= delta;
         }
         if (Bx < 0) {
             delta = ((1 - img[j - 1]) * Bx) / 4;
             deltaB[k] += delta;
             deltaB[k-1] -= delta;
         }

         /*aplicação dos deltas*/
         for (q = 1; q < h - 1; q++)
             for (g = 1; g < w - 1; g++) {
                 k = (q * w + g);
                 j = 3 * k;
                 img[j] += deltaR[k];
                 img[j+2] += deltaB[k];
             }

         /*Verificar over e under flow AQUI*/
         for (j = 0; j < w * h * 3; j += 3) {
             if (img[j] >= 1) img[j] = 255.0/256.0;
             else if (img[j] < 0) img[j] = 0;
             if (img[j+2] >= 1) img[j+2] = 255.0/256.0;
             else if (img[j+2] < 0) img[j+2] = 0;
         }

         /*Correção do G*/
         for (q = 1; q < h - 1; q++)
             for (g = 1; g < w - 1; g++) {
                 j = 3 * (q * w + g);
                 if (img[j] != 0 || img[j + 2] != 0)
                     img[j + 1] = fmod (DOISPI * img[j + 1] + atan (img[j] / img[j + 2]), DOISPI) / DOISPI;
             }

     }
     free (deltaB);
     free (deltaR);
 }

int main (int ac, char* av[]) {
    (void) ac;
    int iN, pN;
    sscanf (av[3], "%d", &iN);
    sscanf (av[4], "%d", &pN);
    omp_set_num_threads (pN);
    ler (av[1]);
    if (w == 3 && h != 3) transformaC (iN, pN);
    else if (w != 3 && h == 3) transformaL (iN, pN);
    else if (w != 3 && h != 3) transforma (iN, pN);
    imprime (av[2]);
    free (img);
    return 0;
}
