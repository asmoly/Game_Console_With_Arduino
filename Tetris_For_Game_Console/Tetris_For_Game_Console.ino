#include <UTFTGLUE.h>             
UTFTGLUE myGLCD(0,A2,A1,A3,A4,A0); 

int backColor[3] = {255, 255, 255};
int gridSize = 24;
int currentColor[3] = {255, 255, 255};

// 0 = blank
// 1 = Light Blue
// 2 = Blue
// 3 = Orange
// 4 = Yellow
// 5 = Purple
// 6 = Green
// 7 = Red

class Board
{
  public:
    Board()
    {  
      for (int i = 0; i < 20; i++)
      {
          for (int j = 0; j < 20; j++)
          {
              int temp[5] = {backColor[0], backColor[1], backColor[2], 0};
            
              for (int z = 0; z < 4; z++)
              {
                boardArr[i][j][z] = temp[z];
              }
          }
      }
    }

    void move_right()
    {
      for (int i = 0; i < 4; i++)
      {
        if (movingBlocks[i][1] - 1 == 20)
        {
          return 0;
        }

        for (int j = 0; j < 3; j++)
        {
          if (boardArr[movingBlocks[i][0]][movingBlocks[i][1] - 1][j] != 255 && boardArr[movingBlocks[i][0]][movingBlocks[i][1] - 1][3] != 1)
          {
            return 0;
          }
        }
      }
      
      for (int i = 0; i < 4; i++)
      {
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][0] = backColor[0];
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][1] = backColor[1];
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][2] = backColor[2];
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][3] = 0;
      }

      for (int i = 0; i < 4; i++)
      {
        movingBlocks[i][1] -= 1; 
        
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][0] = currentColor[0];
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][1] = currentColor[1];
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][2] = currentColor[2];
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][3] = 1;
      }

      //return 0;
    }

    int move_left()
    {
      for (int i = 0; i < 4; i++)
      {
        if (movingBlocks[i][1] + 1 == -1)
        {
          return 0;
        }

        for (int j = 0; j < 3; j++)
        {
          if (boardArr[movingBlocks[i][0]][movingBlocks[i][1] + 1][j] != 255 && boardArr[movingBlocks[i][0]][movingBlocks[i][1] + 1][3] != 1)
          {
            return 0;
          }
        }
      }
      
      for (int i = 0; i < 4; i++)
      {
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][0] = backColor[0];
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][1] = backColor[1];
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][2] = backColor[2];
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][3] = 0;
      }

      for (int i = 0; i < 4; i++)
      {
        movingBlocks[i][1] += 1; 
        
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][0] = currentColor[0];
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][1] = currentColor[1];
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][2] = currentColor[2];
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][3] = 1;
      }

      
      return 0;
    }

    int rotate()
    {
      float averageX = 0;
      float averageY = 0;
      
      for (int i = 0; i < 4; i++)
      {
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][0] = backColor[0];
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][1] = backColor[1];
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][2] = backColor[2];
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][3] = 0;

        averageX += movingBlocks[i][1];
        averageY += movingBlocks[i][0];
      }

      averageX = int(averageX/4);
      averageY = int(averageY/4);

      for (int i = 0; i < 4; i++)
      {
        int localCoords[2] = {movingBlocks[i][1] - averageX, movingBlocks[i][0] - averageY};
        int newLocalCoords[2] = {-1*localCoords[1], 1*localCoords[0]};
        int newWorldCoords[2] = {newLocalCoords[1] + averageY, newLocalCoords[0] + averageX};

        boardArr[newWorldCoords[0]][newWorldCoords[1]][0] = currentColor[0];
        boardArr[newWorldCoords[0]][newWorldCoords[1]][1] = currentColor[1];
        boardArr[newWorldCoords[0]][newWorldCoords[1]][2] = currentColor[2];
        boardArr[newWorldCoords[0]][newWorldCoords[1]][3] = 1;

        movingBlocks[i][0] = newWorldCoords[0];
        movingBlocks[i][1] = newWorldCoords[1];
      }
    }

    void drop()
    {
      while (move_down() != 1)
      {
        Serial.print("droping");
      }
    }

    int move_down()
    {
      for (int i = 0; i < 4; i++)
      {
        if (movingBlocks[i][0] + 1 == 20)
        {
          for (int j = 0; j < 4; j++)
          {
            boardArr[movingBlocks[j][0]][movingBlocks[j][1]][3] = 0;
          }
          
          spawn_in(random(1, 8));
          return 1;
        }

        for (int j = 0; j < 3; j++)
        {
          if (boardArr[movingBlocks[i][0] + 1][movingBlocks[i][1]][j] != 255 && boardArr[movingBlocks[i][0] + 1][movingBlocks[i][1]][3] != 1)
          {
            for (int z = 0; z < 4; z++)
            {
              boardArr[movingBlocks[z][0]][movingBlocks[z][1]][3] = 0;
            }
            spawn_in(random(1, 8));
            return 1;
          }
        }
      }
      
      for (int i = 0; i < 4; i++)
      {
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][0] = backColor[0];
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][1] = backColor[1];
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][2] = backColor[2];
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][3] = 0;
      }

      for (int i = 0; i < 4; i++)
      {
        movingBlocks[i][0] += 1; 
        
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][0] = currentColor[0];
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][1] = currentColor[1];
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][2] = currentColor[2];
        boardArr[movingBlocks[i][0]][movingBlocks[i][1]][3] = 1;
      }

      return 0;
    }

    void check_lines()
    {
      for (int i = 19; i >= 0; i--)
      {
        bool canClear = true;
        
        for (int j = 0; j < 10; j++)
        {
          if (boardArr[i][j][0] == 255 && boardArr[i][j][1] == 255 && boardArr[i][j][2] == 255)
          {
            canClear = false;
          }

          if (boardArr[i][j][3] == 1)
          {
            canClear = false;
          }
        }

        if (canClear == true)
        {
          for (int j = 0; j < 10; j++)
          {
            boardArr[i][j][0] = 255;
            boardArr[i][j][1] = 255;
            boardArr[i][j][2] = 255;
          }

          int z = i - 1;
          for (z; z >= 0; z--)
          {
            for (int x = 0; x < 10; x++)
            {
              if (boardArr[z][x][3] != 1)
              {
                boardArr[z + 1][x][0] = boardArr[z][x][0];
                boardArr[z + 1][x][1] = boardArr[z][x][1];
                boardArr[z + 1][x][2] = boardArr[z][x][2];
  
                boardArr[z][x][0] = 255;
                boardArr[z][x][1] = 255;
                boardArr[z][x][2] = 255;
              }
              
            }
          }
        }
      }
    }

    void spawn_in(int block)
    {
      if (block == 1)
      {
        int newMovingBlocks[4][2] = {{0, 5}, {1, 5}, {2, 5}, {3, 5}};
        currentColor[0] = 0;
        currentColor[1] = 162;
        currentColor[2] = 255;

        for (int i = 0; i < 4; i++)
        {
          for (int j = 0; j < 2; j++)
          {
            movingBlocks[i][j] = newMovingBlocks[i][j];
          }
        }
      }
      else if (block == 2)
      {
        int newMovingBlocks[4][2] = {{0, 4}, {0, 5}, {1, 5}, {2, 5}};
        currentColor[0] = 0;
        currentColor[1] = 0;
        currentColor[2] = 255;

        for (int i = 0; i < 4; i++)
        {
          for (int j = 0; j < 2; j++)
          {
            movingBlocks[i][j] = newMovingBlocks[i][j];
          }
        }
      }
      else if (block == 3)
      {
        int newMovingBlocks[4][2] = {{0, 4}, {0, 5}, {1, 4}, {2, 4}};
        currentColor[0] = 255;
        currentColor[1] = 162;
        currentColor[2] = 0;

        for (int i = 0; i < 4; i++)
        {
          for (int j = 0; j < 2; j++)
          {
            movingBlocks[i][j] = newMovingBlocks[i][j];
          }
        }
      }
      else if (block == 4)
      {
        int newMovingBlocks[4][2] = {{0, 4}, {0, 5}, {1, 4}, {1, 5}};
        currentColor[0] = 255;
        currentColor[1] = 255;
        currentColor[2] = 0;

        for (int i = 0; i < 4; i++)
        {
          for (int j = 0; j < 2; j++)
          {
            movingBlocks[i][j] = newMovingBlocks[i][j];
          }
        }
      }
      else if (block == 5)
      {
        int newMovingBlocks[4][2] = {{0, 4}, {1, 5}, {1, 4}, {1, 3}};
        currentColor[0] = 188;
        currentColor[1] = 0;
        currentColor[2] = 255;

        for (int i = 0; i < 4; i++)
        {
          for (int j = 0; j < 2; j++)
          {
            movingBlocks[i][j] = newMovingBlocks[i][j];
          }
        }
      }
      else if (block == 6)
      {
        int newMovingBlocks[4][2] = {{0, 5}, {1, 5}, {1, 4}, {2, 4}};
        currentColor[0] = 0;
        currentColor[1] = 255;
        currentColor[2] = 0;

        for (int i = 0; i < 4; i++)
        {
          for (int j = 0; j < 2; j++)
          {
            movingBlocks[i][j] = newMovingBlocks[i][j];
          }
        }
      }
      else if (block == 7)
      {
        int newMovingBlocks[4][2] = {{0, 4}, {1, 4}, {1, 5}, {2, 5}};
        currentColor[0] = 255;
        currentColor[1] = 0;
        currentColor[2] = 0;

        for (int i = 0; i < 4; i++)
        {
          for (int j = 0; j < 2; j++)
          {
            movingBlocks[i][j] = newMovingBlocks[i][j];
          }
        }
      }

      

      for (int i = 0; i < 4; i++)
      {
        int temp[4] = {currentColor[0], currentColor[1], currentColor[2], 1};
        
        for (int j = 0; j < 4; j++)
        {
          boardArr[movingBlocks[i][0]][movingBlocks[i][1]][j] = temp[j];
        }
      }
    }

  public:
    int boardArr[20][10][4] = {0};
    int movingBlocks[4][2] = {0};
};

Board board;

void update_ui()
{ 
  for (int i = 0; i < 20; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      myGLCD.setColor(board.boardArr[i][j][0], board.boardArr[i][j][1], board.boardArr[i][j][2]);
      myGLCD.fillRect(i*gridSize, j*gridSize + 35, i*gridSize + gridSize, j*gridSize + gridSize + 35);
    }
  }
}

const int button_delay = 200; // button delay in milliseconds

volatile byte b_r = 0;
volatile byte b_l = 0;
volatile byte b_ro = 0;
volatile byte b_d = 0;

unsigned long button_time = 0;
unsigned long last_button_time = 0;

void button_right_ISR()
{
  button_time = millis();
  if (button_time - last_button_time > button_delay)
  {
    b_r = 1;
    last_button_time = button_time;
  }
}

void button_left_ISR()
{
  button_time = millis();
  if (button_time - last_button_time > button_delay)
  {
    b_l = 1;
    last_button_time = button_time;
  }
  
}

void button_rotate_ISR()
{
  button_time = millis();
  if (button_time - last_button_time > button_delay)
  {
    b_ro = 1;
    last_button_time = button_time;
  }
  
}

void button_drop_ISR()
{
  button_time = millis();
  if (button_time - last_button_time > button_delay)
  {
    b_d = 1;
    last_button_time = button_time;
  }
}

void setup() 
{ 
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);
  pinMode(20, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(21), button_rotate_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(20), button_drop_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(19), button_left_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(18), button_right_ISR, CHANGE);
  
  myGLCD.InitLCD(3);
  myGLCD.setFont(SmallFont);
  board.spawn_in(7);
  update_ui();
  Serial.begin(9600);
}



int counter = 0;

void loop() 
{
  //Serial.print("pressed");
  if (b_d==1)
  {
    board.drop();
    b_d = 0; 
  }
  
  if(b_r==1)
  {
    board.move_right();
    b_r = 0;  
  }

  if(b_l==1)
  {
    board.move_left();
    b_l = 0;  
  }

  if(b_ro==1)
  {
    board.rotate();
    b_ro = 0;  
  }

//  bool state = digitalRead(47);
//  if (state == LOW)
//  {
//    Serial.print("pressed\n");
//  }
  
  if (counter % 100 == 0)
  {
    board.move_down();
    board.check_lines();
    update_ui();
  }

  counter++;
  delay(1);
}
