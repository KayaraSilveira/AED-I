## Enunciado:
1. Monte figuras da sequência de passos da montagem de uma árvore avl
    1. Essa sequencia deve ter as 4 rotações
    2. https://www.cs.usfca.edu/~galles/visualization/AVLtree.html
2. É possível que uma inserção/remoção gere mais do que um rotação dupla? Explique
3. Implemente uma árvore avl. O programa só pergunta 1 número para o usuário item 3.I.a
    1. Primeiro cenário
        1. O programa pergunta quantos nós (n)
        2. O programa automaticamente gera n nós em sequência com valor aleatório e vai adicionando na árvore
            1. Use srand (time(0));
        3. Ao final, use um código de verificação (slide anterior) para validar a árvore e dar ok
    2. Segundo cenário
        1. Após a execução do primeiro cenário deve testar a árvore com os casos mostrado no seguinte link: https://stackoverflow.com/questions/3955680/how-to-check-if-my-avl-tree-implementation-is-correct
