# HTTP-Ripper
Demonstração de ataque de dicionário ao sistema de login de um servidor Web através requisições HTTP em método POST

# Assuntos estudados
- WINSOCK
- Requisições e respostas HTTP
- Manipulação de Strings
- Manipulação de arquivos texto

# Funcionamento
Altere na linha 106 o parâmetro de comparação (if) para identificar senha incorreta com base em algum texto na resposta do servidor Web:
```c
if(instr(0, bufferIn, "Wrong") > -1){
```
Neste caso, a tentativa de login com dados incorretos apresentava uma resposta do servidor que continha em algum lugar a palavra "Wrong".

O arquivo pass.txt deve conter o dicionário de usuários e senhas a serem testados separados por TAB.
Exemplo:
```
user	senha
user	123456
user	qwerty
user	1234
user	user
```

Durante a execução será criado um arquivo relatorio.txt com registro de todas as senhas testadas e um arquivo senhas encontradas.txt quando o login for realizado.

Exemplo arquivo relatorio.txt:
```
teste	teste	[ACESSO NEGADO]
root	admin	[ACESSO NEGADO]
root	admin1234	[ACESSO NEGADO]
root	admin2020	[ACESSO NEGADO]
root	admin20	[ACESSO NEGADO]
sgon4rd	sgon4rd	[ACESSO AUTORIZADO]
root	root	[ACESSO NEGADO]
root	root1234	[ACESSO NEGADO]
root	root20	[ACESSO NEGADO]
```

Exemplo arquivo senhas encontradas.txt:
```
sgon4rd	sgon4rd	[ACESSO AUTORIZADO]
```
