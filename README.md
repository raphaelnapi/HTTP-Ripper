# HTTP-Ripper
Demonstração de ataque de dicionário ao sistema de login de um servidor Web através requisições HTTP em método POST

# Assuntos estudados
- WINSOCK
- Requisições e respostas HTTP
- Manipulação de Strings
- Manipulação de arquivos texto

# Funcionamento
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
