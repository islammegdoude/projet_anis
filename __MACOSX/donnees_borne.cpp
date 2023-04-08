typedef enum _led {OFF, ROUGE, VERT} led;
typedef enum _pwm {STOP, DC, AC_1K, AC_CL} pwm;
typedef struct
{
 // Borne de recharge
 // OUT
 led led_dispo;
 led led_charge;
 led led_defaut;
 led led_prise;
 led led_trappe;
 int contacteur_AC; // 0 ouvert; 1 ferme
 // IN
 int bouton_charge;
 int bouton_stop;
 // Vehicule
 // OUT
 pwm gene_pwm;
 int gene_u;
 int timer_sec; // timer incrementé toutes les secondes
} entrees;