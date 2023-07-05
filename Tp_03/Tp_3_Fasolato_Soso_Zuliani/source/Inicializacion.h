#ifndef INICIALIZACION_H_
#define INICIALIZACION_H_

/* Definiciones */
#define T_MIN		900000
#define SENSOR1		!(PTC->PDIR&(1<<3))
#define SENSOR2		!(PTC->PDIR&(1<<12))
#define V_ON		PTE->PCOR |= (1<<29);	// Rojo
#define V_OFF		PTE->PSOR |= (1<<29);
#define ENABLE_ON	PTD->PCOR |= (1<<5);	// Verde
#define ENABLE_OFF  PTD->PSOR |= (1<<5);
#define TEMP_MAX	1000000
#define DELAY		50000

/* Variables */
typedef enum{
	est_INIT,
	est_ENABLE_ON,
	est_INFRACCION
}Mef_est;

/*
 * Inicializacion de distintos parametros
 */
void vInit(void);
void vMef_Init(Mef_est* estado);
void vMef(Mef_est* estado,int* Temp,int* Delay,bool* Bandera1);
void vEst_Sensor1(int* Temp,int* Delay,bool* Bandera);
void vAntirrebote(int* Delay,bool* Bandera);

#endif /* INICIALIZACION_H_ */
