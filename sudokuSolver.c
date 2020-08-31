#include <stdio.h>

int erlaubteZahlen[9];
int sudoku[9][9], sudokuTemp[9][9], sudokuHorizontal[9][9], sudokuVertikal[9][9];
int sudokuMog[9][9][9];

// Logik Funktionen:
int gibZeile(int block, int kasten);int gibSpalte(int block, int kasten);void setzeErlaubteZahlen(int block, int kasten);int gibEinmaligVertreten(int block, int wert);

// setzeNull Funktionen:
void setzeNullSudoku();void setzeNullSudokuTemp();void setzeNullSudokuHorizontal();void setzeNullSudokuVertikal();void setzeNullSudokuMog();void setzeNullErlaubteZahlen();void setzeNullAlles();

// init Funktionen:
void initSudoku();void initSudokuHorizontal();void initSudokuVertikal();void initSudokuMog();void initEinmaligVertreten();void initControllerErsterDurchlauf();void initSudokuTemp();void initAlles();

// ausgabe Funktionen:
void ausgabeSudoku();

int gibZeile(int block, int kasten) {
  if(block >= 0 && block <= 2) {
    if(kasten >= 0 && kasten <= 2) { return 0;}
    else if(kasten >= 3 && kasten <= 5) { return 1;}
    else if(kasten >= 6 && kasten <= 8) { return 2;}
  }
  else if(block >= 3 && block <= 5) {
    if(kasten >= 0 && kasten <= 2) { return 3;}
    else if(kasten >= 3 && kasten <= 5) { return 4;}
    else if(kasten >= 6 && kasten <= 8) { return 5;}
  }
  else if(block >= 6 && block <= 8) {
    if(kasten >= 0 && kasten <= 2) { return 6;}
    else if(kasten >= 3 && kasten <= 5) { return 7;}
    else if(kasten >= 6 && kasten <= 8) { return 8;}
  }
}
int gibSpalte(int block, int kasten) {
  if(block == 0 || block == 3 || block == 6) {
    if(kasten == 0 || kasten == 3 || kasten == 6) { return 0;}
    else if(kasten == 1 || kasten == 4 || kasten == 7) { return 1;}
    else if(kasten == 2 || kasten == 5 || kasten == 8) { return 2;}
  }
  else if(block == 1 || block == 4 || block == 7) {
    if(kasten == 0 || kasten == 3 || kasten == 6) { return 3;}
    else if(kasten == 1 || kasten == 4 || kasten == 7) { return 4;}
    else if(kasten == 2 || kasten == 5 || kasten == 8) { return 5;}
  }
  else if(block == 2 || block == 5 || block == 8) {
    if(kasten == 0 || kasten == 3 || kasten == 6) { return 6;}
    else if(kasten == 1 || kasten == 4 || kasten == 7) { return 7;}
    else if(kasten == 2 || kasten == 5 || kasten == 8) { return 8;}
  }
}
void setzeErlaubteZahlen(int block, int kasten) {
  setzeNullErlaubteZahlen();

  int verbotenBlock[9] = {0,0,0,0,0,0,0,0,0},
  verbotenZeile[9] = {0,0,0,0,0,0,0,0,0},
  verbotenSpalte[9] = {0,0,0,0,0,0,0,0,0};

  int zeile = gibZeile(block, kasten);
  int spalte = gibSpalte(block, kasten);

  int temp = 0;

  // Initialisiert int verbotenBlock[9].
  for(int xkasten = 0; xkasten < 9; xkasten++) {
    temp = sudoku[block][xkasten]; if(temp == 0) { continue;}
    verbotenBlock[temp-1] = temp;
  }

  // Initialisiert int verbotenZeile[9].
  for(int xspalte = 0; xspalte < 9; xspalte++) {
    temp = sudokuHorizontal[zeile][xspalte]; if(temp == 0) { continue;}
    verbotenZeile[temp-1] = temp;
  }

  // Initialisiert int verbotenSpalte[9].
  for(int xzeile = 0; xzeile < 9; xzeile++) {
    temp = sudokuVertikal[spalte][xzeile]; if(temp == 0) { continue;}
    verbotenSpalte[temp-1] = temp;
  }

  // Initialisiert int erlaubteZahlen[9].
  for(int index = 0; index < 9; index++) {
    temp = verbotenBlock[index] + verbotenZeile[index] + verbotenSpalte[index];
    if(temp == 0) {
      erlaubteZahlen[index] = index + 1;
    }
  }

}
int gibEinmaligVertreten(int block, int wert) {
  int wertZaehler = 0;
  for(int kasten = 0; kasten < 9; kasten++) {
    for(int mog = 0; mog < 9; mog++) {
      if(sudokuMog[block][kasten][mog] == wert) { wertZaehler++;}
    }
  }

  if(wertZaehler == 1) { return 1;}
  else { return 0;}
}

  void setzeNullSudoku() {
    for(int block = 0; block < 9; block++) {
      for(int kasten = 0; kasten < 9; kasten++) {
        sudoku[block][kasten] = 0;
      }
    }
  }
  void setzeNullSudokuTemp() {
    for(int block = 0; block < 9; block++) {
      for(int kasten = 0; kasten < 9; kasten++) {
        sudokuTemp[block][kasten] = 0;
      }
    }
  }
  void setzeNullSudokuHorizontal() {
    for(int zeile = 0; zeile < 9; zeile++) {
      for(int spalte = 0; spalte < 9; spalte++) {
        sudokuHorizontal[zeile][spalte] = 0;
      }
    }
  }
  void setzeNullSudokuVertikal() {
    for(int spalte = 0; spalte < 9; spalte++) {
      for(int zeile = 0; zeile < 9; zeile++) {
        sudokuVertikal[spalte][zeile] = 0;
      }
    }
  }
  void setzeNullSudokuMog() {
    for(int block = 0; block < 9; block++) {
      for(int kasten = 0; kasten < 9; kasten++) {
        for(int mog = 0; mog < 9; mog++) {
          sudokuMog[block][kasten][mog] = 0;
        }
      }
    }
  }
  void setzeNullErlaubteZahlen() {
    for(int index = 0; index < 9; index++) {
      erlaubteZahlen[index] = 0;
    }
  }
void setzeNullAlles() {
  setzeNullSudoku();
  setzeNullSudokuHorizontal();
  setzeNullSudokuVertikal();
  setzeNullSudokuMog();
  setzeNullErlaubteZahlen();
}

  void initSudoku() {
    int tempWert = 0;
    for(int block = 0; block < 9; block++) {
      for(int kasten = 0; kasten < 9; kasten++) {
        printf("Block %d Kasten %d: ", block+1, kasten+1);
        scanf("%d", &tempWert);
        sudoku[block][kasten] = tempWert;
      }
    }
  }
  void initSudokuHorizontal() {
    int block = 0, kasten = 0;
    int zeile = 0, spalte = 0;
    for(int blockReihe = 0; blockReihe < 3; blockReihe++) {
      for(int kastenReihe = 0; kastenReihe < 3; kastenReihe++) {
          sudokuHorizontal[zeile][spalte] = sudoku[block][kasten]; spalte++;
          sudokuHorizontal[zeile][spalte] = sudoku[block][kasten+1]; spalte++;
          sudokuHorizontal[zeile][spalte] = sudoku[block][kasten+2]; spalte++;

          sudokuHorizontal[zeile][spalte] = sudoku[block+1][kasten]; spalte++;
          sudokuHorizontal[zeile][spalte] = sudoku[block+1][kasten+1]; spalte++;
          sudokuHorizontal[zeile][spalte] = sudoku[block+1][kasten+2]; spalte++;

          sudokuHorizontal[zeile][spalte] = sudoku[block+2][kasten]; spalte++;
          sudokuHorizontal[zeile][spalte] = sudoku[block+2][kasten+1]; spalte++;
          sudokuHorizontal[zeile][spalte] = sudoku[block+2][kasten+2]; spalte++;

          kasten += 3;

          spalte = 0;
          zeile++;
      }
      kasten = 0;
      block += 3;
    }
  }
  void initSudokuVertikal() {
    for(int zeile = 0; zeile < 9; zeile++) {
      for(int spalte = 0; spalte < 9; spalte++) {
        sudokuVertikal[spalte][zeile] = sudokuHorizontal[zeile][spalte];
      }
    }
  }
  void initSudokuMog() {
    int temp = 0;
    for(int block = 0; block < 9; block++) {
      for(int kasten = 0; kasten < 9; kasten++) {
        temp = sudoku[block][kasten]; if(temp == 0) { continue;}
        sudokuMog[block][kasten][temp-1] = sudoku[block][kasten];
      }
    }

    for(int block = 0; block < 9; block++) {
      for(int kasten = 0; kasten < 9; kasten++) {
        if(sudoku[block][kasten] == 0) {
          setzeErlaubteZahlen(block, kasten);
          for(int mog = 0; mog < 9; mog++) {
            sudokuMog[block][kasten][mog] = erlaubteZahlen[mog];
          }
        }
      }
    }
    initEinmaligVertreten();
  }
    void initEinmaligVertreten() {
      int temp = 0;
      for(int block = 0; block < 9; block++) {
        for(int kasten = 0; kasten < 9; kasten++) {
          for(int mog = 0; mog < 9; mog++) {
            if(sudokuMog[block][kasten][mog] != 0) {
              if(gibEinmaligVertreten(block, sudokuMog[block][kasten][mog]) == 1) {
                temp = sudokuMog[block][kasten][mog];
                for(int mog2 = 0; mog2 < 9; mog2++) {
                  sudokuMog[block][kasten][mog2] = 0;
                }

                sudokuMog[block][kasten][temp-1] = temp;
              }
            }
          }
        }
      }
    }
  void initControllerErsterDurchlauf() {
    int ungleichZaehler = 0;

    initSudokuTemp();
    while (0 == 0) {
      ungleichZaehler = 0;
      // sudoku mit sudokuTemp gleichsetzen
      for(int block = 0; block < 9; block++) {
        for(int kasten = 0; kasten < 9; kasten++) {
          sudoku[block][kasten] = sudokuTemp[block][kasten];
        }
      }

      // Damit initSudokuMog funktioniert bzw. setzeErlaubteZahlen
      setzeNullSudokuHorizontal(); initSudokuHorizontal();
      setzeNullSudokuVertikal(); initSudokuVertikal();

      // sudokuMog löschen und neu initialisieren
      setzeNullSudokuMog();
      initSudokuMog();
      // sudokuTemp neu initialisieren
      initSudokuTemp();

      // Wenn sudokuTemp anders als sudoku, dann erneut durchführen
      for(int block = 0; block < 9; block++) {
        for(int kasten = 0; kasten < 9; kasten++) {
          if(sudoku[block][kasten] != sudokuTemp[block][kasten]) {
            ungleichZaehler++;
          }
        }
      }
      if(ungleichZaehler == 0) { break;}
    }
  }
    void initSudokuTemp() {
    int zaehler = 0, index = 0;

    for(int block = 0; block < 9; block++) {
      for(int kasten = 0; kasten < 9; kasten++) {
        for(int mog = 0; mog < 9; mog++) {
          if(sudokuMog[block][kasten][mog] != 0) {
            zaehler++;
            index = mog + 1;
          }
        }

        if(zaehler == 1) {
          sudokuTemp[block][kasten] = index;
        }
        zaehler = 0;
        index = 0;
      }
    }
  }
void initAlles() {
  initSudoku();
  initSudokuHorizontal();
  initSudokuVertikal();
  initSudokuMog();
  initControllerErsterDurchlauf();
}

void ausgabeSudoku() {
  int block = 0, kasten = 0;
  for(int blockZeile = 0; blockZeile < 3; blockZeile++) {
    for(int kastenZeile = 0; kastenZeile < 3; kastenZeile++) {
      printf("%d %d %d", sudoku[block][kasten], sudoku[block][kasten+1] ,sudoku[block][kasten+2]);
      printf("  %d %d %d", sudoku[block+1][kasten], sudoku[block+1][kasten+1] ,sudoku[block+1][kasten+2]);
      printf("  %d %d %d\n", sudoku[block+2][kasten], sudoku[block+2][kasten+1] ,sudoku[block+2][kasten+2]);
      kasten += 3;
    }
    printf("\n");
    kasten = 0;
    block += 3;
  }
}
void ausgabeSudokuMog() {
  int kastenZaehler = 0;
  for(int block = 0; block < 9; block++) {
    for(int kasten = 0; kasten < 9; kasten++) {
      if(kastenZaehler == 3) {
        kastenZaehler = 0;
        printf("\n");
      }
      printf("[ ");
      for(int mog = 0; mog < 9; mog++) {
        if(sudokuMog[block][kasten][mog] != 0) { printf("%d ", sudokuMog[block][kasten][mog]);}
      }
      printf("] ");
      kastenZaehler++;
    }
    printf("\n");
  }
}

int main() {
  setzeNullAlles();
  initAlles();
  ausgabeSudoku();
  return 1;
}
