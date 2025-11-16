# Projeto-Embarcados-DGT
#### Sistema embarcado em microcontrolador ESP32 que faz medição da presença de gases nocivos no ar e dispara alerta caso a quantidade exceda um limite de ppm.
---
### Recursos e tecnologias utilizadas

- #### Microcontrolador:
   - EPS32.

- #### Componentes:
   - Breadboard;

   - MQ2 (Sensor de gás);

   - Buzzer.


- #### Tecnologias:
   - IDE: Arduino IDE;

   - Arduino Programming Language;

   - Wokwi;
 
   - Shiftr.io.
---
### Descricao do projeto

O projeto teve como objetivo incentivar a exploração do uso de um microcontrolador para o desenvolvimento de uma aplicação IOT que faz integração com uma plataforma de serviços em nuvem utilizando o protocolo MQTT.

Para o atual projeto utilizamos o simulador online Wokwi para a prototipação do nosso circuito e ligação dos componentes com a placa ESP32. O diagrama eletrônico se encontra neste repositório.

A conexão online foi feita a partir da biblioteca MQTT, utilizando como ssid o ponto de acesso "Wokwi-GUEST" que e uma simulação WiFi, fornecida pelo proprio Wokwi, com acesso total a internet, o que foi indispensável para a prototipagem do projeto.

Com o acesso a internet, utilizamos a plataforma Shiftr.io para a criação de um cloud service que recebe as atualizações dos dados gerados pelo sistema e fizemos a conexão utilizando o protocolo MQTT e conectando ao tópico criado.

---
### Funcionamento

Quando a placa detectar 9 ppm de gás na área, o buzzer será ativado e começará uma contagem de 1 minuto para enviar uma mensagem de aviso ao servidor, alertando as pessoas caso não haja ninguém por perto. Após o envio, se os níveis de gás continuarem altos, o sensor enviará outra mensagem em 5 minutos ao servidor. Para desligar, é necessário verificar se o nível de gás caiu e apertar o botão para desativar o buzzer e as mensagens.
