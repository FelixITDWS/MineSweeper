MineSweeper
===
- 111-2 CSIE of NTUST OOP Lab Project 1

### Mode
- `MineSweeper.exe GUI`: Run the game with GUI
- `MineSweeper.exe CommandInput`: Run the game with console window and control by typing command
- `MineSweeper.exe CommandFile <InputFile> <OutputFile>`: Control by the command from `<InputFile>`, and write the result to `<OutputFile>`

### Information
- Player will win when all the blank is opened except bomb
- Player will lose when any of the bomb is opened
- Every command is able to be use in the operation domain
- GameState: **Standby**, **Playing**, **GameOver**

### Command
- `Load`
  - `BoardFile <file>`: Load board from `<file>`
  - `RandomCount <M> <N> <amount>`: Load board which size is `<M>` * `<N>` and has `<amount>` bomb
  - `RandomRate <M> <N> <rate>`: Load board which size is `<M>` * `<N>` and bomb rate is `<rate>`
- `StartGame`: Start the game
- `Print`
  - `GameState`: Print the current game state
  - `GameBoard`: Print the current game board
  - `GameAnswer`: Print the answer board of the game
  - `BombCount`: Print the amount of bomb
  - `OpenBlankCount`: Print the amount of blank is opened
  - `RemainBlankCount`: Print the amount of blank is not opend
  - `FlagCount`: Print the amount of flag is set
- `LeftClick <row> <col>`: Open the blank of the position
- `RightClick <row> <col>`: Set the mark to the position
- `Replay`: Restart the game
- `Quit`: Exit the game

### Command domain
| Command | Standby | Playing | GameOver |
| :-----: | :-----: | :-----: | :------: |
| `Load` | ✔️ | | |
| `StartGame` | ✔️ | | |
| `Print` | ✔️ | ✔️ | ✔️ |
| `LeftClick` | | ✔️ | |
| `RightClick` | | ✔️ | |
| `Replay` | | | ✔️ |
| `Quit` | | | ✔️ |