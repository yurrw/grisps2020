-- VERIFICAR TIPOS TAMBÉM
-- VERIFICAR SE O SQL TA WORKANDO
-- MIGRAR COMENTARIOS PRA UM PDF 

-- a tabela participantes existe pra armazenar os dados dos frequentadores dos get
-- para isso, salvamos nome e sobrenome, e a forma de comunicação padrão, id do telegram (telegram_id),
-- como nem todos os participantes precisam ser alunos da ufrj- ouvintes, podemos ter identificadores (identificador nacional,...) diferentes
-- e poderiamos ter, por alguma coincidencia, de ter um cpf e um passaporte com mesmo número. Isso acabaria com o principio
-- da unicidade da chave única, assim, criamos um id default pra cada usuario, e o campo id_type e id_num pra armazenar o tipo de identificação 
-- e seu valor. 
CREATE TABLE `participantes` (
  `id` int PRIMARY KEY AUTO_INCREMENT,
  `Nome` varchar(30),
  `Sobrenome` varchar(30),
  `id_type` ENUM ('cpf', 'passaporte', 'dre'),
  `id_num` int,
  `telegram_id` varchar(255)
);
-- Essa tabela é sobre os palestrantes
-- salvamos as informações principais de cada,nome, email,telegram. Como todos os membros do gris precisam ser da ufrj, utilizamos o campo dre como 
-- chave primaria. especialidade serve basicamente para dizzer a área de estudo foco do indivíduo
CREATE TABLE `palestrantes` (
  `dre` int PRIMARY KEY,
  `Nome` varchar(30),
  `Sobrenome` varchar(30),
  `email` varchar(100),
  `telegram_id` varchar(100),
  `especialidade` varchar(255)
);
-- a tabela do get é basicamente sobre as informacoes da palestra
-- titulo, data que foi apresentada, e o assunto debatido. como identificador unico temos um int get_id unico pra cada 
-- get.
CREATE TABLE `get_palestra` (
  `get_id` int PRIMARY KEY AUTO_INCREMENT,
  `titulo` varchar(255),
  `data` timestamp,
  `assunto` varchar(255),
);
-- como cada get pode ter mais de um palestrante, essa tabela serve pra ligar um get a 1 ou n palestrantes.
-- basicamente contém a chave primaria , get_id, que se referencia ao get  e o palestrante_id que referencia ao palestrante.
-- a utilizacao das duas juntas caracteriza uma chave primeira composta (VERIFICAR DEPOIS)
CREATE TABLE `get_palestrante` (
  `get_id` int,
   CONSTRAINT fk_getpalestrante_get_id FOREIGN KEY (get_id) REFERENCES get_palestra(get_id),
  `palestrante_id` int,
   CONSTRAINT fk_getpalestrante_palestrante_id FOREIGN KEY (palestrante_id) REFERENCES palestrantes(dre)
);
-- a tabela get guarda as informações das avaliações que podem ser passadas em cada get
-- get_id é a chave estrangeira que relaciona a tabela com os gets. tag_id é a idenficação unica. O resto é auto-descritivo.
CREATE TABLE `tag` (
  `tag_id` int PRIMARY KEY AUTO_INCREMENT,
  `get_id` int,
  `data_entrega` timestamp,
  `titulo` varchar(100),
  `descricao` varchar(255)
);
-- aqui é o onde relacionamos a nota de cada avaliação (tag) com cada participante
-- Eu aqui normalmente usaria uma chave primeira composta com o conjunto de tag_id e participante_id (as duas estrangeiras)
-- mas como pede uma chave primaria, criei uma ava_id pra ser esse idenficador unico. 
-- fora isso temos também armazenado nela a data de entrega da pessoa, que pode ser comparadao com a data de entrega da tabela tag
-- para saber se a pessoa entregou atrasado ou nao
CREATE TABLE `avaliacao_nota` (
  `ava_id` int,
  `tag_id` int,
  `participante_id` int,
  `nota` int,
  `data_entrega` timestamp
);
ALTER TABLE `get_palestra` ADD FOREIGN KEY (`palestrantes`) REFERENCES `palestrantes` (`dre`);

ALTER TABLE `tag` ADD FOREIGN KEY (`get_id`) REFERENCES `get_palestra` (`get_id`);

ALTER TABLE `avaliacao_nota` ADD FOREIGN KEY (`tag_id`) REFERENCES `tag` (`tag_id`);

ALTER TABLE `avaliacao_nota` ADD FOREIGN KEY (`participante_id`) REFERENCES `participantes` (`id`);
