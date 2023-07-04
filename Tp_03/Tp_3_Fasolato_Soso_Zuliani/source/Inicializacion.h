#ifndef INICIALIZACION_H_
#define INICIALIZACION_H_

/* Definiciones */
#define T_MIN		900000
#define SENSOR		!(PTC->PDIR&(1<<3))
#define V_ON		PTE->PCOR |= (1<<29);
#define V_OFF		PTE->PSOR |= (1<<29);
#define V_TOGGLE	PTE->PTOR |= (1<<29);
#define TEMP_MAX	1000000
#define DELAY		50000

/* Variables */
typedef enum{
	est_INIT,
	est_SENSOR1,
	est_SENSOR2
}Mef_est;

/*
 * Inicializacion de distintos parametros
 */
void vInit(void);
void vMef_Init(Mef_est* estado);
void vMef(Mef_est* estado,int* Temp,int* Delay,bool* Bandera1);
void vEst_Sensor1(int* Temp,int* Delay,bool* Bandera);
void vEst_Sensor2(int* Temp,int* Delay,bool* Bandera);
void vAntirrebote(int* Delay,bool* Bandera);

#endif /* INICIALIZACION_H_ */
