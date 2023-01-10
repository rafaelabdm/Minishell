<h1 align="center">
	✏️ Minishell
</h1>

<p align="center"><br>
Esse projeto é sobre criar um simples shell. Sim, seu próprio bash<i>izinho</i>. Você aprenderá muito sobre processos e descritores de arquivos.<br>
This project is about creating a simple shell. Yes, your own little bash. You will learn a lot about processes and file descriptors.<br>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/rafaelabdm/so_long?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/rafaelabdm/so_long?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/rafaelabdm/so_long?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/rafaelabdm/so_long?color=green" />
</p>

<p align="center">
<SUB>Por Rafaela Bustamante e Raphael dos Santos Esteves, cadetes na 42 São Paulo.</SUB>
</p>

---

<h2>🐚 Sobre o projeto</h2>

> _As beautiful as a shell_
<p>
Nesse projeto criamos o nosso próprio bash, em uma escala menor. O propósito dele é nos fazer trabalhar com múltiplos processos, 
file descriptors, tratamento de entrada do usuário, entre diversos outros desafios menores.<br>
Ao realizar esse projeto ganhamos o conhecimento de como o bash funciona por baixo dos panos, como nosso input é tratado e como os 
comandos dados a ele são executados.<br>
O Minishell é um projeto muito desafiador, por ser longo e ser o primeiro projeto colaborativo do currículo, forçando não apenas o  nosso 
treinamento técnico, com o código em si, mas também nossas habilidades de comunicação, em todas as trocas com a sua dupla durante todo o processo). <br>
Embora trabalhoso, é um projeto muito divertido e com um retorno de conhecimento e sentimento de realização enormes.
<br>
</p>

<h2>🤓 Um pouco sobre as etapas do código</h2>

<p>
🔪<b> PARSER:</b> A primeira coisa a se fazer é separar o input do usuário e tipar cada argumento recebido. Para isso fizemos uma separação de processos, 
separando os inputs por cada '|' pipe encontrado e depois pelos espaços (tratamento especial quando há aspas). Isso nos deixava cada arumento em um token, 
onde conseguíamos tipar o que aquele token era: comando simples, argumento, buildin, arquivo, redirecionamento, etc.<br>
📖<b> EXPANDER:</b> Feito os tokens, o expander rodava eles em busca do '$' e das aspas para a expansão das variáveis de ambiente e remoção das aspas. 
Caso o expander encontrasse a variável descrida depois do símbulo ($), ele a substituia pelo seu valor (guardado na nossa variável envp), caso contrário, 
substituia pur vazio (""). Já as aspas, seguindo algumas regras, eram removidas do token.<br>
🏁<b> EXECUTER:</b> Com os tokens prontos para montar os comandos, o executor os juntavam em um array de strings (formato aceito pela função execve). 
Verificava a quantidade de processos, checando a quantidade de pipes, e abria processos filhos para lidar com os comandos. Checava o caminho
disponível da variável PATH e passava para a função execve. O único caso em que o comando é rodado no processo pai é quando temos apenas um processo/comando 
e este é um Build-in. Os Build-ins serão descritos no próximo tópico.<br>
</p>

<p>
🔨 <b>BUILD-INS:</b><br>
◦ ECHO <i>(with option -n)</i>: printar os argumentos passados a ele.<br>
◦ CD <i>(with only a relative or absolute path)</i>: trocar de diretório. <br>
◦ PWD <i>(with no options)</i>: mostrar diretório atual. <br>
◦ EXPORT <i>(with no options)</i>: exportar as variáveis passadas como argumentos. <br>
◦ UNSET <i>(with no options)</i>: remover as variáveis passadas como argumentos.<br>
◦ ENV <i>(with no options or arguments)</i>: mostrar as variáveis de ambiente. <br>
◦ EXIT <i>(with no options)</i>: sair do minishell. <br>
</p>

<h2>💻 COMO USAR:</h2>

<p>
<b>Comando do terminal:</b> <TT> ./minishell </TT>;<br>
<SUB>Você precisa da biblioteca da externa <i>readline</i> instalada.</SUB><br>
<SUB>Os build-ins tem limitações de options, em caso de dúvida confiria descrição acima.</SUB>
</p>
