if (speed == 60) {
    if (pista[(curPos + 1) % d][0] == 0) {
        pista[(curPos + 1) % d][0] = thNum;
        pista[curPos][0] = 0;
        cyclers[thNum].ds += 1;
    }
    else if (pista[(curPos + 1) % d][1] == 0) {
        pista[(curPos + 1) % d][1] = thNum;
        pista[curPos][1] = 0;
        cyclers[thNum].ds += 1;
    }
    round = 0;
}
else { /*speed == 30*/
    if (round == 1) {
        round = 0;
        if (pista[(curPos + 1) % d][0] == 0) {
            pista[(curPos + 1) % d][0] = thNum;
            pista[curPos][0] = 0;
            cyclers[thNum].ds += 0.5;
        }
        else if (pista[(curPos + 1) % d][1] == 0) {
            pista[(curPos + 1) % d][1] = thNum;
            pista[curPos][1] = 0;
            cyclers[thNum].ds += 0.5;
        }
    }
    else {
        round = 1;
        cyclers[thNum].ds += 0.5;
    }
}










if (speed == 60 || (speed == 30 && round == 1)) {
    round = 0;

    if (pista[(curPos + 1) % d][0] == 0) {
        pista[(curPos + 1) % d][0] = thNum;
        pista[curPos][0] = 0;
        cyclers[thNum].ds += 1;
    }
    else if (pista[(curPos + 1) % d][1] == 0) {
        pista[(curPos + 1) % d][1] = thNum;
        pista[curPos][1] = 0;
        cyclers[thNum].ds += 1;
    }
}
else /*speed == 30 && round == 0*/ round = 1;





curPos = floor (cyclers[thNum].ds + cyclers[thNum].initPos);
nextPos = floor (cyclers[thNum].ds + cyclers[thNum].initPos + speed) % d;

if (pista[nextPos][0] == 0) {
    pista[curPos][0] = 0;
    pista[nextPos][0] = thNum;
    cyclers[thNum].ds += speed;
}
else if (pista[nextPos][1] == 0) {
    pista[curPos][1] = 0;
    pista[NextPos][1] = thNum;
    cyclers[thNum].ds += speed;
}








if (speed == 60) {
    if (pista[(curPos + 1) % d][0] == 0) {
        pista[(curPos + 1) % d][0] = thNum;
        pista[curPos][0] = 0;
        cyclers[thNum].ds += 1;
    }
    else if (pista[(curPos + 1) % d][1] == 0) {
        pista[(curPos + 1) % d][1] = thNum;
        pista[curPos][1] = 0;
        cyclers[thNum].ds += 1;
    }
}
else { /*speed == 30*/

}
