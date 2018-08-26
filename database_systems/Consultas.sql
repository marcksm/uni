/*******************************************************************************
                            Consultas.sql

    Neste arquivo estão todas as consultas SQL utilizadas em nosso projeto.
    Utilizamos, em alguns casos, os próprios métodos do Django para interação
    com o banco de dados. Nestes casos, escrevemos neste arquivo o equivalente
    em SQL.

    Na verdade, as consultas abaixo são pseudo-SQL. Algumas consultas depedem
    de parâmetros variáveis. Estes parâmetros foram escritos nas consultas sql
    abaixo entre colchetes angulares. (ex: <p_id>)

*******************************************************************************/

/* Consultas no app desenvolvedor */
SELECT p.* FROM desenvolvedor_trabalha_em as t, projeto_projeto as p WHERE t.user_id=<u_id> and p.id=t.projeto_id
SELECT a.* FROM desenvolvedor_trabalha_em as t, auth_user as a WHERE t.projeto_id = <p_id> and a.id = t.user_id
SELECT * FROM desenvolvedor_trabalha_em WHERE user_id = <u_id> AND projeto_id = <p_id>;
SELECT * FROM projeto_projeto WHERE id = <p_id>;
SELECT username FROM auth_user WHERE id = <u_id>;
INSERT INTO auth_user (username, first_name, last_name, email, password, is_superuser, is_staff, is_active, date_joined) VALUES (<nome de usuario>, <nome>, <sobrenome>, <email>, <hash da senha>, 'f', 'f', 't', now());
UPDATE auth_user SET first_name = <nome>, last_name = <sobrenome>, email = <email>, password = <hash da senha> WHERE id = <u_id>;
DELETE FROM auth_user WHERE id = <u_id>;
SELECT id FROM desenvolvedor_trabalha_em WHERE user_id = <u_id>;

/* Consultas no app tarefa */
SELECT * FROM projeto_projeto WHERE id = <p_id>;
SELECT * FROM tarefa_tarefa WHERE id = <t_id>;
SELECT t.* FROM tarefa_tarefa as t, projeto_projeto as p WHERE t.projeto_id = p.id AND t.projeto_id = <p_id>;
DELETE FROM tarefa_tarefa WHERE id = <t_id>;
INSERT INTO tarefa_tarefa (nome, descricao, deadline, estado, user_id, projeto_id) VALUES (<n>, <d>, <de>, <e>, <uid>, <pid>);
UPDATE tarefa_tarefa SET nome=<n>, descricao=<d>, deadline=<de>, estado=<e> WHERE id = <t_id>;

/* Consultas no app projeto */
SELECT * FROM projeto_projeto ORDER BY id DESC LIMIT 10;
SELECT * FROM projeto_projeto;
SELECT * FROM projeto_projeto WHERE id = <p_id>;
SELECT * FROM desenvolvedor_trabalha_em WHERE projeto_id = <p>;
SELECT * FROM auth_users WHERE username = <dev>;
SELECT * FROM desenvolvedor_trabalha_em WHERE user_id = <q_user> AND projeto_id = <p>;
INSERT INTO desenvolvedor_trabalha_em (user_id, projeto_id) VALUES (<q_user>, <p>);
UPDATE projeto_projeto SET nome = <e_nome>, descricao = <e_descricao>, estado = <e_estado> WHERE id = <e_id>;
INSERT INTO projeto_projeto (nome, descricao) VALUES (<n_nome>, <n_descricao>);
DELETE FROM desenvolvedor_trabalha_em WHERE projeto_id = <p>;
DELETE FROM projeto_projeto WHERE id = <p_id>

/* Consultas no app requisito */
SELECT * FROM projeto_projeto WHERE id = <p_id>;
SELECT * FROM requisito_requisito WHERE id = <r_id>;
SELECT * FROM requisito_requisito WHERE id = <r_id> AND projeto_id = <p_id>;
SELECT * FROM requisito_funcionalidades WHERE requisito_id = <r_id> AND id = <f_id>;
SELECT * FROM requisito_requisito WHERE projeto_id = <p_id>;
SELECT * FROM requisito_funcionalidades WHERE requisito_id = <r_id>;
DELETE FROM requisito_funcionalidades WHERE id = <f_id> AND requisito_id = <r_id>;
DELETE FROM requisito_requisito WHERE id = <r_id> AND projeto_id = <p_id>;
INSERT INTO requisito_requisito (titulo, descricao, projeto_id) VALUES (<t>, <d>, <pid>);
UPDATE requisito_requisito SET titulo=<t>, descricao=<d> WHERE id = <r_id>;
INSERT INTO requisito_funcionalidades (descricao, projeto_id) VALUES (<d>, <pid>);
UPDATE requisito_funcionalidades SET descricao=<d> WHERE id = <f_id>;
