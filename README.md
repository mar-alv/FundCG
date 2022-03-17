# FCG2022-1

# Exercício 1) O que é a GLSL? Quais os dois tipos de shaders são obrigatórios no pipeline programável da versão atual que trabalhamos em aula e o que eles processam?

Assim como HLSL, é uma linguagem de shader que trabalha com programas executados na GPU. Tem como shaders obrigatórios:
- Vertex Shader, que posiciona os vértices nas coordenadas finais antes do OpenGL rasterizar a geomentri para 2D
- Fragment Shader, rodam para cada fragmento entre os vértices

# Exercício 2) O que são primitivas gráficas? Como fazemos o armazenamento dos vértices na OpenGL?
- Representação de uma forma geométrica

# Exercício 3) Explique o que é VBO, VAO e EBO, e como se relacionam (se achar mais fácil, pode fazer um gráfico representando a relação entre eles). 
- VBO: Buffer/Array, normalmente de float, que envia dados dos vértices diretamente na memória da GPU, permitindo que objs sejam renderizados mais rapdiamente pela place gráfica
- VAO: Fazem a ligação dos atributos de um vértice(Posições, cores, normais) e define qual VBOserá usado, localização dos dados deles e seus formatos.
- EBO: Faz associação da ideia de índices, evitando que vértices sejam replicadas no VBO

# Exercício 4) Analise o código fonte do projeto Hello Triangle. Localize e relacione os conceitos de shaders, VBOs e VAO apresentados até então. Não precisa entregar nada neste exercício. 
