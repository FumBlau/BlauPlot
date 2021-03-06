#include <Time.h>
#include <TimeLib.h>



/* RobotReloj
 Modificado por elprofegarcia.com  original de Johannes Heberlein 2014
 v 1.02 ES
La librería Time la puede descargar en http://elprofegarcia.com/?page_id=2
 o en http://playground.arduino.cc/Code/time  y debe copiarla a al subdirectorio /libraries dentro 
 del directorio donde tenga instalado Arduino

Conexiones entre Servos y Arduino:

Servo de elevacion ->  Pin 2 del Arduino  (cable Naranja del servo)
Servo izquierdo    ->  Pin 3 del Arduino  (cable Naranja del servo)
Servo derecho      ->  Pin 4 del Arduino  (cable Naranja del servo)
Los cables rojos de los Servos deben conectarse al Pin de 5V del Arduino
Los cables Marron de los Servos deben conectarse al Pin  GND del Arduino


Primero debe calibrar los brazos para que varíen en Angulo de 90 grados exactos y de forma cruzada entre el servo derecho e izquierdo.

Después de Calibrar, borre o marque como comentario la línea siguiente  */

#define HORAS 16
#define MINUTOS 30

//#define CALIBRACION

// En modo de calibración, ajuste el factor siguiente hasta que los servos se mueven exactamente 90 grados
#define SERVOFAKTOR 640  //#define SERVOFAKTOR 620
/* En modo de calibración, ajuste los valores NULL para que los brazos de los servos esten en todo momento paralelos Ya sea al eje X o Y */
#define SERVOLEFTNULL 1800 //#define SERVOLEFTNULL 1900
#define SERVORIGHTNULL 1000 //#define SERVORIGHTNULL 984

#define SERVOPINELEVADOR  2      //  Pin 2 conexión del servo elevador 
#define SERVOPINIZQUIERDO  3     //  Pin 3 conexión del servo izquierdo
#define SERVOPINDERECHA 4    //  Pin 4 conexión del servo derecho

// definir posiciones del servo elevador
#define LIFT0 700// en la superficie de borrado
#define LIFT1 1000  // elevación entre escritura de numeros
#define LIFT2 1000   //#define LIFT2 725  // yendo con el borrador

// velocidad de brazo elevador, un número mayor es más lento
#define VELOCIDADELEVADOR 1500

// longitud de los brazos
#define L1 35
#define L2 60    //#define L2 55.1
#define L3 13.2


// puntos de origen de servo izquierda y derecha
#define O1X 23
#define O1Y -24
#define O2X 46
#define O2Y -24



#include <Servo.h>

int servoLift = 1500;

Servo servo1;  // 
Servo servo2;  // 
Servo servo3;  //  

volatile double lastX = 75;
volatile double lastY = 47.5;

int last_min = 0;

void setup() 
{ 
  // Ajuste la hora actual, sólo el primero en valores,: hh, mm  es necesario
 setTime(HORAS,MINUTOS,0,0,0,0);

  drawTo(70, 43);
  lift(0);
  servo1.attach(SERVOPINELEVADOR);  //  servo elevador 
  servo2.attach(SERVOPINIZQUIERDO);  //  servo izquierdo
  servo3.attach(SERVOPINDERECHA);  //  servo derecho
  delay(1000);

} 

void loop() 
{ 

#ifdef CALIBRACION

  // los brazos de los servos tendran 90 ° entre los movimientos, paralelo al eje X e Y
  drawTo(-3, 29.2);
  delay(500);
  drawTo(74.1, 28);
  delay(500);

#else 


  int i = 0;
  if (last_min != minute()) {

    if (!servo1.attached()) servo1.attach(SERVOPINELEVADOR);
    if (!servo2.attached()) servo2.attach(SERVOPINIZQUIERDO);
    if (!servo3.attached()) servo3.attach(SERVOPINDERECHA);

    lift(0);

    hour();
    while ((i+1)*10 <= hour())
    {
      i++;
    }

    number(3, 3, 111, 1);
    number(5, 25, i, 0.9);
    number(19, 25, (hour()-i*10), 0.9);
    number(28, 25, 11, 0.9);

    i=0;
    while ((i+1)*10 <= minute())
    {
      i++;
    }
    number(34, 25, i, 0.9);
    number(48, 25, (minute()-i*10), 0.9);
    lift(2);
    //drawTo(74.2, 47.5);
    drawTo(70, 43);
    lift(1);
    last_min = minute();

    servo1.detach();
    servo2.detach();
    servo3.detach();
  }

#endif

} 

// Escribir el  numeral de bx por ser el punto de origen parte inferior izquierda. La escala 1 es igual a una alta fuente de 20 mm. 
// La estructura sigue a este principio: mover al primer punto de inicio del numeral, levante hacia abajo, dibuje numeral, levante
void number(float bx, float by, int num, float scale) {

  switch (num) {

  case 0:
    drawTo(bx + 12 * scale, by + 6 * scale);
    lift(0);
    bogenGZS(bx + 7 * scale, by + 10 * scale, 10 * scale, -0.8, 6.7, 0.5);
    lift(1);
    break;
  case 1:

    drawTo(bx + 3 * scale, by + 15 * scale);
    lift(0);
    drawTo(bx + 10 * scale, by + 20 * scale);
    drawTo(bx + 10 * scale, by + 0 * scale);
    lift(1);
    break;
  case 2:
    drawTo(bx + 2 * scale, by + 12 * scale);
    lift(0);
    bogenUZS(bx + 8 * scale, by + 14 * scale, 6 * scale, 3, -0.8, 1);
    drawTo(bx + 1 * scale, by + 0 * scale);
    drawTo(bx + 12 * scale, by + 0 * scale);
    lift(1);
    break;
  case 3:
    drawTo(bx + 2 * scale, by + 17 * scale);
    lift(0);
    bogenUZS(bx + 5 * scale, by + 15 * scale, 5 * scale, 3, -2, 1);
    bogenUZS(bx + 5 * scale, by + 5 * scale, 5 * scale, 1.57, -3, 1);
    lift(1);
    break;
  case 4:
    drawTo(bx + 10 * scale, by + 0 * scale);
    lift(0);
    drawTo(bx + 10 * scale, by + 20 * scale);
    drawTo(bx + 2 * scale, by + 6 * scale);
    drawTo(bx + 12 * scale, by + 6 * scale);
    lift(1);
    break;
  case 5:
    drawTo(bx + 2 * scale, by + 5 * scale);
    lift(0);
    bogenGZS(bx + 5 * scale, by + 6 * scale, 6 * scale, -2.5, 2, 1);
    drawTo(bx + 5 * scale, by + 20 * scale);
    drawTo(bx + 12 * scale, by + 20 * scale);
    lift(1);
    break;
  case 6:
    drawTo(bx + 2 * scale, by + 10 * scale);
    lift(0);
    bogenUZS(bx + 7 * scale, by + 6 * scale, 6 * scale, 2, -4.4, 1);
    drawTo(bx + 11 * scale, by + 20 * scale);
    lift(1);
    break;
  case 7:
    drawTo(bx + 2 * scale, by + 20 * scale);
    lift(0);
    drawTo(bx + 12 * scale, by + 20 * scale);
    drawTo(bx + 2 * scale, by + 0);
    lift(1);
    break;
  case 8:
    drawTo(bx + 5 * scale, by + 10 * scale);
    lift(0);
    bogenUZS(bx + 5 * scale, by + 15 * scale, 5 * scale, 4.7, -1.6, 1);
    bogenGZS(bx + 5 * scale, by + 5 * scale, 5 * scale, -4.7, 2, 1);
    lift(1);
    break;

  case 9:
    drawTo(bx + 9 * scale, by + 11 * scale);
    lift(0);
    bogenUZS(bx + 7 * scale, by + 15 * scale, 5 * scale, 4, -0.5, 1);
    drawTo(bx + 5 * scale, by + 0);
    lift(1);
    break;

  case 111:

    lift(0);
    drawTo(70, 46);
    drawTo(65, 43);

    drawTo(65, 49);
    drawTo(5, 49);
    drawTo(5, 45);
    drawTo(65, 45);
    drawTo(65, 40);

    drawTo(5, 40);
    drawTo(5, 35);
    drawTo(65, 35);
    drawTo(65, 30);

    drawTo(5, 30);
    drawTo(5, 25);
    drawTo(65, 25);
    drawTo(65, 20);

    drawTo(5, 20);
    drawTo(60, 44);

    drawTo(70, 43);
    lift(2);

    break;

  case 11:
    drawTo(bx + 5 * scale, by + 15 * scale);
    lift(0);
    bogenGZS(bx + 5 * scale, by + 15 * scale, 0.1 * scale, 1, -1, 1);
    lift(1);
    drawTo(bx + 5 * scale, by + 5 * scale);
    lift(0);
    bogenGZS(bx + 5 * scale, by + 5 * scale, 0.1 * scale, 1, -1, 1);
    lift(1);
    break;

  }
}



void lift(char lift) {
  switch (lift) {
    // sitio para optimizar  !

  case 0: //850

      if (servoLift >= LIFT0) {
      while (servoLift >= LIFT0) 
      {
        servoLift--;
        servo1.writeMicroseconds(servoLift);        
        delayMicroseconds(VELOCIDADELEVADOR);
      }
    } 
    else {
      while (servoLift <= LIFT0) {
        servoLift++;
        servo1.writeMicroseconds(servoLift);
        delayMicroseconds(VELOCIDADELEVADOR);

      }

    }

    break;

  case 1: //150

    if (servoLift >= LIFT1) {
      while (servoLift >= LIFT1) {
        servoLift--;
        servo1.writeMicroseconds(servoLift);
        delayMicroseconds(VELOCIDADELEVADOR);

      }
    } 
    else {
      while (servoLift <= LIFT1) {
        servoLift++;
        servo1.writeMicroseconds(servoLift);
        delayMicroseconds(VELOCIDADELEVADOR);
      }

    }

    break;

  case 2:

    if (servoLift >= LIFT2) {
      while (servoLift >= LIFT2) {
        servoLift--;
        servo1.writeMicroseconds(servoLift);
        delayMicroseconds(VELOCIDADELEVADOR);
      }
    } 
    else {
      while (servoLift <= LIFT2) {
        servoLift++;
        servo1.writeMicroseconds(servoLift);        
        delayMicroseconds(VELOCIDADELEVADOR);
      }
    }
    break;
  }
}


void bogenUZS(float bx, float by, float radius, int start, int ende, float sqee) {
  float inkr = -0.05;
  float count = 0;

  do {
    drawTo(sqee * radius * cos(start + count) + bx,
    radius * sin(start + count) + by);
    count += inkr;
  } 
  while ((start + count) > ende);

}

void bogenGZS(float bx, float by, float radius, int start, int ende, float sqee) {
  float inkr = 0.05;
  float count = 0;

  do {
    drawTo(sqee * radius * cos(start + count) + bx,
    radius * sin(start + count) + by);
    count += inkr;
  } 
  while ((start + count) <= ende);
}


void drawTo(double pX, double pY) {
  double dx, dy, c;
  int i;

  // dx dy of new point
  dx = pX - lastX;
  dy = pY - lastY;
  // Longitud de la trayectoria en mm, 4 veces equivale a 4 pasos por mm
  c = floor(4 * sqrt(dx * dx + dy * dy));

  if (c < 1) c = 1;

  for (i = 0; i <= c; i++) {
    // dibuja la línea punto por punto
    set_XY(lastX + (i * dx / c), lastY + (i * dy / c));

  }

  lastX = pX;
  lastY = pY;
}

double return_angle(double a, double b, double c) {
  // regla del coseno para el angulo entre c y a
  return acos((a * a + c * c - b * b) / (2 * a * c));
}

void set_XY(double Tx, double Ty) 
{
  delay(1);
  double dx, dy, c, a1, a2, Hx, Hy;

  //calcular triangulo entre marcador, servo izquierdo y brazo
  // cartesiano dx/dy
  dx = Tx - O1X;
  dy = Ty - O1Y;

  // longitud polar (c)  y el angulo (a1)
  c = sqrt(dx * dx + dy * dy); 
  a1 = atan2(dy, dx); 
  a2 = return_angle(L1, L2, c);

  servo2.writeMicroseconds(floor(((a2 + a1 - M_PI) * SERVOFAKTOR) + SERVOLEFTNULL));

  // calcular el punto del brazo joinr para el triángulo del  servo derecho y el brazo
  a2 = return_angle(L2, L1, c);
  Hx = Tx + L3 * cos((a1 - a2 + 0.621) + M_PI); //36,5°
  Hy = Ty + L3 * sin((a1 - a2 + 0.621) + M_PI);

  // calcular el triángulo entre el marcador, servo derecho y el brazo
  dx = Hx - O2X;
  dy = Hy - O2Y;

  c = sqrt(dx * dx + dy * dy);
  a1 = atan2(dy, dx);
  a2 = return_angle(L1, (L2 - L3), c);

  servo3.writeMicroseconds(floor(((a1 - a2) * SERVOFAKTOR) + SERVORIGHTNULL));

}




