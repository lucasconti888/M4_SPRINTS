#include <WiFi.h>                         //biblioteca WiFi


// ============================================================================
// --- Mapeamento de Hardware ---
#define   led1   6
#define   led2   8 
#define   led3   3
#define   led4   35
#define   led5   47
#define   led6   20               
#define   buzzer   16                    


// ============================================================================
// --- Constantes Auxialires ---
const char *ssid     = "Inteli-COLLEGE";  //atribuir nome da rede WiFi
const char *password = "QazWsx@123"; //atribuir senha da rede


// ============================================================================
// --- Objetos ---
WiFiServer server(80);                    //define a porta que o servidor irá utilizar
                                          //(normalmente utiliza-se a porta padrão 80)

// ============================================================================
// --- Protótipo das Funções ---
void relay_wifi();                       //função para gerar web server e controlar os relés
                                

// ============================================================================

void setup() 
{
  Serial.begin(115200);              
  pinMode(led1, OUTPUT);               
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(buzzer, OUTPUT);          

  Serial.println();                      //
  Serial.print("Conectando-se a ");      //
  Serial.println(ssid);                  //
  WiFi.begin(ssid, password);            //inicializa WiFi, passando o nome da rede e a senha

  while(WiFi.status() != WL_CONNECTED)   //aguarda conexão (WL_CONNECTED é uma constante que indica sucesso na conexão)
  {
    delay(741);                          //
    Serial.print(".");                   //vai imprimindo pontos até realizar a conexão...
  }

  Serial.println("");                    //mostra WiFi conectada
  Serial.println("WiFi conectada");      //
  Serial.println("Endereço de IP: ");    //
  Serial.println(WiFi.localIP());        //mostra o endereço IP

  server.begin();                        //inicializa o servidor web

}


// ============================================================================
// --- Loop Infinito ---
void loop() 
{


  while(WiFi.status() != WL_CONNECTED)   //aguarda conexão (WL_CONNECTED é uma constante que indica sucesso na conexão)
  {
    WiFi.begin(ssid, password);          //inicializa WiFi, passando o nome da rede e a senha
    Serial.print(".");                   //vai imprimindo pontos até realizar a conexão...

    delay(741);                          //741ms
  }
  
  relay_wifi();                                //chama função para controle dos relés por wifi


  
} //end loop


// ============================================================================
// --- relay_wifi ---
void relay_wifi()
{

  WiFiClient client = server.available();      //verifica se existe um cliente conectado com dados a serem transmitidos
  
  if(client)                                   //existe um cliente?
  {                                            //sim
    Serial.println("Novo Cliente Definido");   //informa por serial
    String currentLine = "";                   //string para armazenar a mensagem do cliente
    
    while(client.connected())                  //repete enquanto o cliente estiver conectado
    {
      
      if(client.available())                   //existem dados a serem lidos?
      {                                        //sim
        char c=client.read();                  //salva em c
        Serial.write(c);                       //mostra na Serial
        
        if(c=='\n')                            //é um caractere de nova linha?
        {                                      //sim
          if(currentLine.length()==0)          //a mensagem terminou?
          {                                    //sim
            //gera a página HTML
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<center><br><h1>Quiz </h2><br>");
            client.print("<h2>Primeira pergunta para o jogador 1</h2><br>");
            client.print("<h2>Qual estrela dos anos 80 e reconhecida pelo Guinness World Records como a artista feminina mais vendida de todos os tempos?</h2><br>");            
            client.print("<h2>A) <a href=\"/H1\">Lady Gaga</a></h2><br>");
            client.print("<h2>B) <a href=\"/H2\">Madonna</a></h2><br>");
            client.print("<h2>C) <a href=\"/H1\">Taylor Swift</a></h2><br>");
            client.print("<h2>D) <a href=\"/H1\">Cindy Lauper</a></h2><br></center>");
            client.println();
          
            break;                             //encerra o laço
            
            
          } //end if currentLine.length
          
          else currentLine="";                 //senão, impede string de ficar com espaços em branco
        
        } //end if c
                  
        else if(c != '\r') currentLine += c;  //adicionamos o caractere como parte da mensagem, se diferene de retorno/nova linha

       //verifica para ligar ou desligar os relés
          if(currentLine.endsWith("GET /H1")){
            tone(buzzer, 500);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 400);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 300);
            delay(500); 
            noTone(buzzer);
            digitalWrite(led1, HIGH);
            digitalWrite(led2, HIGH);
            digitalWrite(led3, HIGH);
            digitalWrite(led4, HIGH);
            digitalWrite(led5, HIGH);
            digitalWrite(led6, HIGH);
            delay(100); 
            digitalWrite(led1, LOW);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Errado, o certo era Madonna, vez do jogador 2, clique <a href=\"/H3\">AQUI</a> para continuar.</h2><br>");
            client.println();
            break;                 
          };
          if(currentLine.endsWith("GET /H2")){
            tone(buzzer, 1000);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 800);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 1000);
            delay(300); 
            noTone(buzzer);
            digitalWrite(led1, HIGH);
            digitalWrite(led2, HIGH);
            digitalWrite(led3, HIGH);
            digitalWrite(led4, HIGH);
            digitalWrite(led5, HIGH);
            digitalWrite(led6, HIGH);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Voce acertou!!Vez do jogador 2, clique <a href=\"/H3\">AQUI</a> para continuar.</h2><br>");
            client.println();
            break; 
          };

          if(currentLine.endsWith("GET /H3")){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>David Bowie apareceu em que filme em 1986?</h2><br>");
            client.print("<h2>A) <a href=\"/H4\">Laranja Mecânica</a></h2><br>");
            client.print("<h2>B) <a href=\"/H4\">Star Wars</a></h2><br>");
            client.print("<h2>C) <a href=\"/H4\">Titanic</a></h2><br>");
            client.print("<h2>D) <a href=\"/H5\">Labirinto</a></h2><br>");
            client.println();
            break;
          };

          if(currentLine.endsWith("GET /H5")){
            tone(buzzer, 1000);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 800);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 1000);
            delay(300); 
            noTone(buzzer);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Voce acertou!!Vez do jogador 1, clique <a href=\"/H6\">AQUI</a> para continuar.</h2><br>");
            client.println();
            break;
          };

          if(currentLine.endsWith("GET /H4")){
            tone(buzzer, 500);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 400);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 300);
            delay(500); 
            noTone(buzzer);
            digitalWrite(led4, LOW);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Errado, o certo era Labirinto, vez do jogador 1, clique <a href=\"/H6\">AQUI</a> para continuar.</h2><br>");
            client.println();
            break;
          };

          if(currentLine.endsWith("GET /H6")){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>De que pais vem o iconico trio pop A-ha?</h2><br>");
            client.print("<h2>A) <a href=\"/H7\">Noruega</a></h2><br>");
            client.print("<h2>B) <a href=\"/H8\">Gana</a></h2><br>");
            client.print("<h2>C) <a href=\"/H8\">Marrocos</a></h2><br>");
            client.print("<h2>D) <a href=\"/H8\">Inglaterra</a></h2><br>");
            client.println();
            break;
          };

          if(currentLine.endsWith("GET /H8")){
            tone(buzzer, 500);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 400);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 300);
            delay(500); 
            noTone(buzzer);
            digitalWrite(led2, LOW);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Errado, o certo era Noruega, vez do jogador 2, clique <a href=\"/H9\">AQUI</a> para continuar.</h2><br>");
            client.println();
            break;
          };

          if(currentLine.endsWith("GET /H7")){
            tone(buzzer, 1000);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 800);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 1000);
            delay(300); 
            noTone(buzzer);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Voce acertou!!Vez do jogador 2, clique <a href=\"/H9\">AQUI</a> para continuar.</h2><br>");
            client.println();
            break;
          };

          if(currentLine.endsWith("GET /H9")){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>QQual cantora ganhou um Grammy de melhor nova artista em 1985?</h2><br>");
            client.print("<h2>A) <a href=\"/l1\">Cindy Lauper</a></h2><br>");
            client.print("<h2>B) <a href=\"/l2\">Madonna</a></h2><br>");
            client.print("<h2>C) <a href=\"/l2\">Lara Croft</a></h2><br>");
            client.print("<h2>D) <a href=\"/l2\">Bonnie Tyler</a></h2><br>");
            client.println();
            break;
          
          };


          if(currentLine.endsWith("GET /l1")){
            tone(buzzer, 1000);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 800);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 1000);
            delay(300); 
            noTone(buzzer);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Voce acertou!!Vez do jogador 1, clique <a href=\"/l3\">AQUI</a> para continuar.</h2><br>");
            client.println();
            break;
          };
          
          if(currentLine.endsWith("GET /l2")){
            tone(buzzer, 500);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 400);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 300);
            delay(500); 
            noTone(buzzer);
            digitalWrite(led5, LOW);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Errado, o certo era Cindy Lauper, vez do jogador 1, clique <a href=\"/l3\">AQUI</a> para continuar.</h2><br>");
            client.println();
            break;
          };

          if(currentLine.endsWith("GET /l3")){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Qual desses atores / atrizes morreu em 2016?</h2><br>");
            client.print("<h2>A) <a href=\"/l4\">Alex Crumbles</a></h2><br>");
            client.print("<h2>B) <a href=\"/l5\">Carrie Fisher</a></h2><br>");
            client.print("<h2>C) <a href=\"/l4\">James Kaldwin</a></h2><br>");
            client.print("<h2>D) <a href=\"/l4\">Cindy Lauper</a></h2><br>");
            client.println();
            break;
          
          };

          if(currentLine.endsWith("GET /l5")){
            tone(buzzer, 1000);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 800);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 1000);
            delay(300); 
            noTone(buzzer);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Voce acertou!!Vez do jogador 2, clique <a href=\"/l6\">AQUI</a> para continuar.</h2><br>");
            client.println();
            break;
          };

          if(currentLine.endsWith("GET /l4")){
            tone(buzzer, 500);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 400);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 300);
            delay(500); 
            noTone(buzzer);
            digitalWrite(led3, LOW);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Voce Errou eram Carrie Fisher!!Vez do jogador 2, clique <a href=\"/l6\">AQUI</a> para continuar.</h2><br>");
            client.println();
            break;
          };

          if(currentLine.endsWith("GET /l6")){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h2>Qual desses e um personagem de One piece?</h2><br>");
            client.print("<h2>A) <a href=\"/l8\">Luffy</a></h2><br>");
            client.print("<h2>B) <a href=\"/l7\">Naruto</a></h2><br>");
            client.print("<h2>C) <a href=\"/l7\">Billy</a></h2><br>");
            client.print("<h2>D) <a href=\"/l7\">Cindy Lauper</a></h2><br>");
            client.println();
            break;
          
          };

          if(currentLine.endsWith("GET /l8")){
            tone(buzzer, 1000);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 800);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 1000);
            delay(300); 
            noTone(buzzer);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h1>Voce acertou!!Veja quem tem mais leds ligadas para saber quem ganhou!.</h2><br>");
            client.println();
            break;
          };

          if(currentLine.endsWith("GET /l7")){
            tone(buzzer, 500);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 400);
            delay(100); 
            noTone(buzzer);
            tone(buzzer, 300);
            delay(500); 
            noTone(buzzer);
            digitalWrite(led6, LOW);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<h1>Voce Errou era Luffy!!Veja quem tem mais leds ligadas para saber quem ganhou!</h2><br>");
            client.println();
            break;
          };
       
      } //end if client.available()
      
    } //end if while client.connected

    client.stop();                           //finaliza conexão
    Serial.println("Client Disconnected.");
    
  } //end if client  
  
  
} //end relay_wifi









/* ========================================================   
 
                                                              
======================================================== */
/* --- Final do Programa --- */