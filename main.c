#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//convert the string char* string into the item_form 
//index = 0 -> empty, 1 -> king_white, 2 -> king_black, 3 -> queen_white, 4 -> queen_black, 5 -> root_white, 6 -> rook_black, 7 -> bishop_white, 8 -> bishop_black, 9 -> knight_white, 10 = knight_black, 11 -> pawn_white, 12 -> pawn_black;

//if side = 1 -> white
//if side = 2 -> black

#define STANDARD_GAME_START "rnbkqbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"
#define STANDARD_CONVERSION_TYPE "_KkQqRrBbNnPp"

const int KNIGHT_DEFAULT_LEGAL_MOVES[] = {6,10,15,17,-6,-10,-15,-17,0};
const int KING_DEFAULT_LEGAL_MOVES[] = {1,7,8,9,-1,-7,-8,-9,0};
const int QUEEN_DEFAULT_LEGAL_MOVES[] = {1,2,3,4,5,6,7,-1,-2,-3,-4,-5,-6,-7,8,16,24,32,40,48,56,-8,-16,-24,-32,-40,-48,-56,9,18,27,36,45,54,63,-9,-18,-27,-36,-45,-54,-63,7,14,21,28,35,42,49,-7,-14,-21,-28,-35,-42,-49,0};
const int ROOT_DEFAULT_LEGAL_MOVES[] = {1,2,3,4,5,6,7,-1,-2,-3,-4,-5,-6,-7,8,16,24,32,40,48,56,-8,-16,-24,-32,-40,-48,-56,0};
const int BISHOP_DEFAULT_LEGAL_MOVES[] = {9,18,27,36,45,54,63,-9,-18,-27,-36,-45,-54,-63,7,14,21,28,35,42,49,-7,-14,-21,-28,-35,-42,-49,0};
const int PAWN_WHITE_DEFAULT_LEGAL_MOVES[] = {7,8,9,16,0};
const int PAWN_BLACK_DEFAULT_LEGAL_MOVES[] = {-7,-8,-9,-16,0};

int side_in_pos(int pos, int* game)
{
  switch(game[pos])
  {
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:
    case 11: return 1; break;
    case 2:
    case 4:
    case 6:
    case 8:
    case 10:
    case 12: return 2; break;
    default: return 0;
  }
  return -1;
}

int move_king_legal(int from, int to, int* game)
{
  for (int i = 0; KING_DEFAULT_LEGAL_MOVES[i] != 0; i++)
  {
    if (KING_DEFAULT_LEGAL_MOVES[i] == (to - from))
    {
      return 1;
    }
  }
  return 0;
}

int move_knight_legal(int from, int to, int* game)
{
  for (int i = 0; KNIGHT_DEFAULT_LEGAL_MOVES[i] != 0; i++)
  {
    if (KNIGHT_DEFAULT_LEGAL_MOVES[i] == (to - from))
    {
      return 1;
    }
  }
  return 0;
}

int move_queen_legal(int from, int to, int* game)
{
  for (int i = 0; QUEEN_DEFAULT_LEGAL_MOVES[i] != 0; i++)
  {
    if (QUEEN_DEFAULT_LEGAL_MOVES[i] == (to - from))
    {
      return 1;
    }
  }
  return 0;
}

int move_root_legal(int from, int to, int* game)
{
  for (int i = 0; ROOT_DEFAULT_LEGAL_MOVES[i] != 0; i++)
  {
    if (ROOT_DEFAULT_LEGAL_MOVES[i] == (to - from))
    {
      int index = ROOT_DEFAULT_LEGAL_MOVES[i];
      if (index < 8 && index > -8)
      {
        if (index > 0)
        {
          for (int j = from+1; j <= from + index - 1; j++)
          {
            if (game[j] != 0)
            {
              return 0;
            }
          }
          return 1;
        }
        else
        {
          for (int j = from-1; j >= from + index + 1; j--)
          {
            if (game[j] != 0)
            {
              return 0;
            }
          }
          return 1;
        }
      }
      else
      {
        if (index > 0)
        {
          for (int j = from+8; j <= from + index - 8; j += 8)
          {
            if (game[j] != 0)
            {
              return 0;
            }
          }
          return 1;
        }
        else
        {
          for (int j = from-8; j >= from + index + 8; j -= 8)
          {
            if (game[j] != 0)
            {
              return 0;
            }
          }
          return 1;
        }
      }
    }
  }
  return 0;
}

int move_bishop_legal(int from, int to, int* game)
{
  for (int i = 0; BISHOP_DEFAULT_LEGAL_MOVES[i] != 0; i++)
  {
    if (BISHOP_DEFAULT_LEGAL_MOVES[i] == (to - from))
    {
      return 1;
    }
  }
  return 0;
}

int move_pawn_white_legal(int from, int to, int* game)
{
  for (int i = 0; PAWN_WHITE_DEFAULT_LEGAL_MOVES[i] != 0; i++)
  {
    if (PAWN_WHITE_DEFAULT_LEGAL_MOVES[i] == (to - from))
    {
      int index = PAWN_WHITE_DEFAULT_LEGAL_MOVES[i];
      if (from > 15 && index == 16)
      {
        return 0;
      }
      if (index == 7 && game[from + 7] == 0)
      {
        return 0;
      }
      if (index == 9 && game[from + 9] == 0)
      {
        return 0;
      }
      if (index == 8 && game[from + 8] != 0)
      {
        return 0;
      }
      return 1;
    }
  }
  return 0;
}

int move_pawn_black_legal(int from, int to, int* game)
{
  for (int i = 0; PAWN_BLACK_DEFAULT_LEGAL_MOVES[i] != 0; i++)
  {
    if (PAWN_BLACK_DEFAULT_LEGAL_MOVES[i] == (to - from))
    {
      int index = PAWN_BLACK_DEFAULT_LEGAL_MOVES[i];
      if (from < 48 && index == -16)
      {
        return 0;
      }
      if (index == -7 && game[from - 7] == 0)
      {
        return 0;
      }
      if (index == -9 && game[from - 9] == 0)
      {
        return 0;
      }
      if (index == -8 && game[from - 8] != 0)
      {
        return 0;
      }
      return 1;
    }
  }
  return 0;
}

int legal_move(int from, int to, int* game, int turn)
{
  if (game[from] == 0 || side_in_pos(from, game) == side_in_pos(to, game) || from > 63 || to > 63 || from < 0 || to < 0 || side_in_pos(from, game) != turn)
  {
    return 0;
  }
  switch (game[from])
  {
    case 1:
    case 2: return move_king_legal(from, to, game);
    case 3:
    case 4: return move_queen_legal(from, to, game);
    case 5:
    case 6: return move_root_legal(from, to, game);
    case 7:
    case 8: return move_bishop_legal(from, to, game);
    case 9:
    case 10: return move_knight_legal(from, to, game);
    case 11: return move_pawn_white_legal(from, to, game);
    case 12: return move_pawn_black_legal(from, to, game);
    default: return 0;
  }
  return -1;
}

int move(int from, int to, int* current_game, int turn)
{
  if (!legal_move(from, to, current_game, turn))
  {
    return 0;
  }
  int holder;
  holder = current_game[from];
  current_game[from] = 0;
  current_game[to] = holder;
  return 1;
}

int* convert_string_into_array(char* string)
{
  int* result_array;
  result_array = calloc(64, sizeof(int));
  int i = 0, x = 0, y = 7;
  do
  {
    switch(string[i])
    {
      case '/': x = 0; y--; break;
      case 'K': result_array[y * 8 + x] = 1; x++; break;
      case 'k': result_array[y * 8 + x] = 2; x++; break;
      case 'Q': result_array[y * 8 + x] = 3; x++; break;
      case 'q': result_array[y * 8 + x] = 4; x++; break;
      case 'R': result_array[y * 8 + x] = 5; x++; break;
      case 'r': result_array[y * 8 + x] = 6; x++; break;
      case 'B': result_array[y * 8 + x] = 7; x++; break;
      case 'b': result_array[y * 8 + x] = 8; x++; break;
      case 'N': result_array[y * 8 + x] = 9; x++; break;
      case 'n': result_array[y * 8 + x] = 10; x++; break;
      case 'P': result_array[y * 8 + x] = 11; x++; break;
      case 'p': result_array[y * 8 + x] = 12; x++; break;
      default: x += atoi(&string[i]);
    }
    if (x > 7)
    {
      x = 7;
    }
    i++;
  }while (string[i] != '\0');
  return result_array;
}

void show_current_table(int* current_game_in_int, char* conversion_type, int show_table)
{
  for (int i = 7; i >= 0; i--)
  {
    for (int j = 0; j < 8; j++)
    {
      printf("%c ", conversion_type[current_game_in_int[i * 8 + j]]);
    }
    if (show_table)
    {
      printf("  ");
      for (int j = 0; j < 8; j++)
      {
        printf("%2d ", i * 8 + j);
      }
    }
    printf("\n");
  }
}

int main(void) {
  char* input_string;
  int* matrix_of_table;
  char* conversion_type;
  int move_from, move_to, show_table = 0, turn = 1;

  input_string = calloc(73, sizeof(char));
  conversion_type = calloc(14, sizeof(char));
  //fgets(input_string, 72, stdin);
  strcpy(input_string, STANDARD_GAME_START);
  strcpy(conversion_type,STANDARD_CONVERSION_TYPE);
  
  matrix_of_table = convert_string_into_array(input_string);

  printf("Show Table at the side? y=1, n=0: ");
  scanf("%d", &show_table);

  for (;;)
  {
    show_current_table(matrix_of_table, conversion_type, show_table);
    printf("\n");
    scanf("%d %d", &move_from, &move_to);
    printf("\n");
    if (!move(move_from, move_to, matrix_of_table, turn))
    {
      printf("Invalid Move!\n");
      continue;
    }
    if (turn == 1)
    {
      turn = 2;
    }
    else
    {
      turn = 1;
    }
  }

  return 0;
}
