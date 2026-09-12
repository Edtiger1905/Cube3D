# cub3D

## English Version
*This project has been created as part of the 42 curriculum by epandele, evera.*

### Description
cub3D is a graphic design project that involves creating a "realistic" 3D graphical representation of the inside of a maze from a first-person perspective. It is built using the miniLibX library and relies on ray-casting principles, heavily inspired by the world-famous Wolfenstein 3D game (the first FPS ever created). The main goal is to explore ray-casting, apply mathematics for elegant algorithms, and create a dynamic view inside a maze where the player must find their way.

### Instructions
**Compilation:**
The project is written in C and must be compiled using `cc` with the flags `-Wall -Wextra -Werror`. 
Run `make` at the root of the repository to compile the project. The provided Makefile includes the following rules: `all`, `clean`, `fclean`, `re`, and `bonus`.

**Execution:**
The program requires a scene description file with the `.cub` extension as its first argument.
```bash
./cub3D maps/example.cub
```

**Controls:**
- **W, A, S, D**: Move the point of view through the maze.
- **Left / Right Arrows**: Look left and right.
- **ESC**: Close the window and quit the program cleanly.
- **Red Cross**: Clicking the red cross on the window's frame will also close the program cleanly.

### Resources
- **Raycasting:** Lode's Computer Graphics Tutorial (Raycasting) is highly recommended for understanding the math behind the engine.
- **Graphics:** MiniLibX documentation.
- **AI Usage:** AI tools were used primarily to help structure documentation and brainstorm logic for the map parsing module. All AI-generated suggestions were thoroughly reviewed, tested, and validated with peers to ensure full understanding and proper implementation.

---

## Versione Italiana
*This project has been created as part of the 42 curriculum by evera, epandele.*
*(Questo progetto è stato creato come parte del curriculum 42 da evera, epandele.)*

### Descrizione
cub3D è un progetto di grafica che consiste nel creare una rappresentazione grafica 3D "realistica" dell'interno di un labirinto da una prospettiva in prima persona. È sviluppato utilizzando la libreria miniLibX e si basa sui principi del ray-casting, fortemente ispirato al famoso gioco Wolfenstein 3D (il primo FPS mai creato). L'obiettivo principale è esplorare il ray-casting, applicare la matematica per creare algoritmi eleganti e realizzare una vista dinamica all'interno di un labirinto in cui il giocatore deve trovare la propria strada.

### Istruzioni
**Compilazione:**
Il progetto è scritto in C e deve essere compilato usando `cc` con i flag `-Wall -Wextra -Werror`.
Esegui `make` nella root della repository per compilare il progetto. Il Makefile fornito include le seguenti regole: `all`, `clean`, `fclean`, `re` e `bonus`.

**Esecuzione:**
Il programma richiede un file di descrizione della scena con estensione `.cub` come primo argomento.
```bash
./cub3D maps/example.cub
```

**Comandi:**
- **W, A, S, D**: Muovi il punto di vista attraverso il labirinto.
- **Frecce Sinistra / Destra**: Guarda a sinistra e a destra.
- **ESC**: Chiudi la finestra ed esci dal programma in modo pulito.
- **Croce Rossa**: Cliccando sulla croce rossa della cornice della finestra si chiuderà il programma in modo pulito.

### Risorse
- **Raycasting:** Il tutorial di Lode's Computer Graphics (Raycasting) è caldamente consigliato per comprendere la matematica dietro al motore grafico.
- **Grafica:** Documentazione di MiniLibX.
- **Uso dell'IA:** Gli strumenti di intelligenza artificiale sono stati utilizzati principalmente per strutturare la documentazione e raccogliere idee per la logica del modulo di parsing della mappa. Tutte le soluzioni generate dall'IA sono state attentamente revisionate, testate e validate con i colleghi per garantire una comprensione completa e una corretta implementazione.