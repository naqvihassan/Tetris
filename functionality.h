/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */


//----HASSAN NAQVI---//
//----22i-0797_C----//

//---Piece Starts to Fall When Game Starts---//




/////////////////////////////////////////////
///* START CODING YOUR FUNTIONS HERE *///
void fallingPiece(float &timer, float &delay, int &colorNum)
{

    if (timer > delay)
    {
        int p = M - 1;
        for (int i = 0; i < 4; i++)
        {
            point_2[i][0] = point_1[i][0];
            point_2[i][1] = point_1[i][1];

            // How much units downward

            point_1[i][1] += 1;
        }

        if (!anamoly())
        {

            //--- Un-Comment this Part When You Make BLOCKS array---//
            int n = rand() % 7;
            for (int i = 0; i < 4; i++)

                gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
            colorNum = 1 + rand() % 7;

            for (int i = 0; i < 4; i++)
            {
                point_1[i][0] = BLOCKS[n][i] % 2;

                point_1[i][1] = BLOCKS[n][i] / 2;
            }
        }
        timer = 0;
    }
}
//-------DirectBase----//

void fallspace(bool &button)
{


    while (anamoly())
    {

        for (int i = 0; i < 4; ++i)                 
        {

            point_1[i][1]++;                        //It goes down untill it reach base.
        }
    }
}
//-------Move--------//

void movement(int &delta_x)
{
    for (int i = 0; i < 4; i++)
    {
        point_2[i][0] = point_1[i][0];                  
        point_1[i][0] += delta_x;
    }
    if (!anamoly())
    {
        for (int i = 0; i < 4; i++)
        {
            point_1[i][0] = point_2[i][0];                      
        }
    }
}

//---------Rotating---------//
void rotation(bool &rotate)
{
    if (rotate)
    {
        for (int i = 0; i < 4; i++)
        {
            point_2[i][0] = point_1[i][0];                          //Use this as a center of rotation 
            point_2[i][1] = point_1[i][1];
            int x = point_1[i][1] - point_1[1][1];
            int y = point_1[i][0] - point_1[1][0];
            point_1[i][0] = point_1[1][0] - x;
            point_1[i][1] = point_1[1][1] + y;
        }
    }
    if (!anamoly())
    {
        for (int i = 0; i < 4; i++)

        {
            point_1[i][0] = point_2[i][0];                  //Use point_2 as temporary array and replace it when needed
            point_1[i][1] = point_2[i][1];
        }
    }
}

void myshadow()
{

    for (int i = 0; i < 4; i++)
    {
        yourshadow[i][0] = point_1[i][0];
        yourshadow[i][1] = point_1[i][1];                   // Same position as point_1
    }
    while (my_anamoly())

        for (int i = 0; i < 4; i++)                         //Shadow goes down untill it reach base 
            yourshadow[i][1] += 1;
    if (!my_anamoly())
    {

        for (int i = 0; i < 4; i++)
        {
            yourshadow[i][1] -= 1;                          
        }
    }
}

void CompleteLine()
{
    int x = M - 1;

    for (int j = M - 1; j > 0; j--)
    {
        int count = 0;
        for (int i = 0; i < N; i++)
        {

            if (gameGrid[j][i])                                 //Count the number of bocks in 1 row
                count++;

            gameGrid[x][i] = gameGrid[j][i];
        }
        if (count < N)
            x--;                                                
    }
}

///* YOUR FUNCTIONS END HERE *///
/////////////////////////////////////