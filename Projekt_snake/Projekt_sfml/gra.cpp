#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>

const int H = 16; 


using namespace sf;

 std::string Mapa1[H] ={
						"AAAAAAAAAAAAAAAA",
						"A              A",
						"A              A",
						"A              A",
						"A         MMM  A",
						"A              A",
						"A              A",
						"A              A",
						"A              A",
						"A              A",
						"A              A",
						"A              A",
						"A              A",
						"A              A",
						"A              A",
						"AAAAAAAAAAAAAAAA",
						};
	

struct snake {
    int *x;
	int *y;
	int leng;
};

void dynamicLeng(int i, int j, snake &ss);
bool setStartupLeng(int i, int j, snake &ss);
void changeValue(int i, int j, snake &ss);
Vector2i cordGenerator();

int main(){
		
	snake ss = {NULL, NULL, 0};
 
      

	 sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Application");
	//------------------------------------------------------
	Texture testkura_boczna;
	testkura_boczna.loadFromFile("tekstury\\boki.png");
	testkura_boczna.setSmooth(true);
	//------------------------------------------------------
	Texture testkura_snake;
	testkura_snake.loadFromFile("tekstury\\snake.png");
	testkura_snake.setSmooth(true);
	//------------------------------------------------------
	Texture testkura_do_zjedzenia;
	testkura_do_zjedzenia.loadFromFile("tekstury\\zjedzmnie.png");
	testkura_do_zjedzenia.setSmooth(true);
	//------------------------------------------------------

	float time ;
	enum kierunek { gora,dol, prawo,lewo, nic};
	int direct = lewo;

	bool startupLeng = true;
	bool eatSth = false;
	bool sthToEat = false;
	bool drawIt = false;

	//------------------------------------------------------

	Sprite bloki_mapy;
	bloki_mapy.setScale(0.25, 0.25);
	Vector2i cords;

	Clock cc;
	//cc.restart();

	int it = 0;
	
	Vector2i pos;
		

			
 
        while( window.isOpen() ){
		
			time = cc.getElapsedTime().asMilliseconds();
 
                sf::Event event;
                while ( window.pollEvent(event) ){
 
                        switch(event.type)
			{
			case Event::Closed:
				window.close();
				break;

		    case Event::KeyReleased:
				 
			
					switch(event.key.code){
	
				case Keyboard::Up:
					if(direct == dol) direct = dol;
					else
					direct = gora;
				break;
				case Keyboard::Down:
					if(direct == gora) direct = gora;
					else
				direct= dol;
				
				break;
				case Keyboard::Left:
					if(direct == prawo) direct = prawo;
					else
				direct= lewo;
				
				break;
				case Keyboard::Right:
					if(direct == lewo) direct = lewo;
					else
				direct = prawo;
				
				
				break;
		}
                }
				}
				

				window.clear(Color(0,0,0));

				
					//---------------------------------------
					//rysowanie mapy + generoweanie gowna do zjedzenia
					//--------------------------------------- 
				if(!sthToEat){
					 cords = cordGenerator();
						Mapa1[cords.x][cords.y] = 'E';
					 sthToEat = true;
				}

				for (int i=0; i<H; i++){
					for (int j=0; j<H; j++){


							if (Mapa1[i][j]==' ')  continue;
							if (Mapa1[i][j]=='A') bloki_mapy.setTexture(testkura_boczna);
							if(Mapa1[i][j] =='E') bloki_mapy.setTexture(testkura_do_zjedzenia);
							if (Mapa1[i][j]=='M') {

								bloki_mapy.setTexture(testkura_snake);


								if(startupLeng == true) startupLeng = setStartupLeng(i,j,ss);
								else if( eatSth == true) dynamicLeng(i,j, ss);
								//std::cout<<startupLeng<<std::endl;
							}
									//for(int k = 0; k < ss.leng; k++) std::cout<< ss.x[k]<<" "<<ss.y[k]<<" ";
									//std::cout<<std::endl;
									 bloki_mapy.setPosition(j*64,i*64) ;
									 window.draw(bloki_mapy);
										   }
							}
						
			
					//---------------------------------------
					//ruszanie sie + powiekszanie 
					//--------------------------------------- 


				if(time == 500 && !startupLeng) {
					
					if(Mapa1[ss.x[0] - 1][ss.y[0]]!='A' && direct == gora){ 

						if(Mapa1[ss.x[0] - 1][ss.y[0]]=='E'){
							
							//Mapa1[ss.x[0] + 1][ss.y[0]] = 'M';
							sthToEat = false;
							dynamicLeng(ss.x[ss.leng - 1],ss.y[ss.leng - 1], ss);
							//std::cout<<"dotykam"<<std::endl;
						}
						Mapa1[ss.x[0] - 1][ss.y[0]] = 'M';
						
						changeValue( -1, 0, ss);
						
					}else if((Mapa1[ss.x[0] - 1][ss.y[0]]=='A' && direct == gora)) {
						window.close();
					}


					if(Mapa1[ss.x[0] + 1][ss.y[0]] !='A' && direct == dol) {

						if(Mapa1[ss.x[0] + 1][ss.y[0]]=='E'){
							
							//Mapa1[ss.x[0] + 1][ss.y[0]] = 'M';
							sthToEat = false;
							dynamicLeng(ss.x[ss.leng - 1],ss.y[ss.leng - 1], ss);
							//std::cout<<"dotykam"<<std::endl;
						}

						Mapa1[ss.x[0] + 1][ss.y[0]] = 'M';
						changeValue( 1, 0, ss);

					}else if((Mapa1[ss.x[0] + 1][ss.y[0]] =='A' && direct == dol)){
						window.close();
					}

					if(Mapa1[ss.x[0]][ss.y[0] + 1] !='A' && direct == prawo){

						if(Mapa1[ss.x[0]][ss.y[0] + 1]=='E'){
						//Mapa1[ss.x[0]][ss.y[0] + 1] = 'M';
							sthToEat = false;
							dynamicLeng(ss.x[ss.leng - 1],ss.y[ss.leng - 1], ss);
							//std::cout<<"dotykam"<<std::endl;

						}
						Mapa1[ss.x[0]][ss.y[0] + 1] = 'M';
						changeValue( 0, 1, ss);
					}else if((Mapa1[ss.x[0]][ss.y[0] + 1] =='A' && direct == prawo)){
						window.close();
					}

					if((Mapa1[ss.x[0]][ss.y[0] - 1] !='A' && direct == lewo)){

						if(Mapa1[ss.x[0]][ss.y[0] - 1]=='E'){
						
									//Mapa1[ss.x[0]][ss.y[0] - 1] = 'M';
									sthToEat = false;
									dynamicLeng(ss.x[ss.leng - 1],ss.y[ss.leng - 1], ss);
									//std::cout<<"dotykam"<<std::endl;
								}
						Mapa1[ss.x[0]][ss.y[0] - 1] = 'M';
						changeValue( 0, -1, ss);

					}else if((Mapa1[ss.x[0]][ss.y[0] - 1] =='A' && direct == lewo)){
						window.close();
					}

					
					
					cc.restart();

				}	

				//---------------------------------------
				//ruszanie sie + powiekszanie 
				//--------------------------------------- 
				for(int i = 1 ; i< ss.leng ; i++) {
						 if((ss.x[0] ==  ss.x[i] && ss.y[0] == ss.y[i])) window.close();
					}
				
							    window.display();
											  
             	
						}
				 
				   return 0;
		}
					
Vector2i cordGenerator(){

	srand( time(NULL));

	bool getCord = false;
	Vector2i cords;

	while(!getCord){

		cords.x = 1 + rand()%15;
		cords.y = 1 + rand()%15;

		if(Mapa1[cords.x][cords.y] == ' ') getCord = true;

	}
	//std::cout<<"zwracam true"<<std::endl;

	return cords;
		
};          

bool setStartupLeng(int i, int j, snake &ss){
							
								if( ss.leng == 0){
									ss.leng++;
									ss.x = new int[1];
									ss.x[0] = i;
									ss.y = new int[1];
									ss.y[0] = j;
									return true;

								}else{ 
									//std::cout<<ss.leng<<std::endl;
									dynamicLeng(i, j , ss);
									if(ss.leng < 3) return true;
									
							}
	
	return false;
};

void dynamicLeng(int i, int j, snake &ss){

							   ss.leng++;
							   int *tmpX = ss.x;
							   int *tmpY = ss.y;
							   ss.x = new int[ss.leng];
							   ss.y = new int[ss.leng];

							   for(int k = 0; k < ss.leng-1 ; k++) ss.x[k] = tmpX[k];
							   for(int k = 0; k < ss.leng-1 ; k++) ss.y[k] = tmpY[k];

							   ss.x[ss.leng -1] = i;
							   ss.y[ss.leng-1] = j;
				
							   delete[] tmpX;
							   delete[]	tmpY;

	
};

void changeValue(int i, int j, snake &ss){

							   int *tmpX = ss.x;
							   int *tmpY = ss.y;


							   ss.x = new int[ss.leng];
							   ss.y = new int[ss.leng];

							   ss.x[0] = tmpX[0] + i;
							   ss.y[0] = tmpY[0] + j;

							   std::cout<<*ss.x << *ss.y<<std::endl;
				
							   for(int k = 1; k < ss.leng ; k++) {
								   ss.x[k] = tmpX[k-1];
								   ss.y[k] = tmpY[k-1];
							   }

							   Mapa1[tmpX[ss.leng -1]][tmpY[ss.leng -1]] = ' ';

							  // std::cout<<"wykonalem caly krok dla "<< i<<std::endl;

							   delete[] tmpX;
							   delete[]	tmpY;


}
