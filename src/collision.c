#include <avr/io.h>

#include "bits.h"
#include "collision.h"

void InitCollision() {
	/* Data direction */
	COLLISION_DIR &= ~COLLISION_PINS;
	
	/* Pull-up */
	COLLISION_PORT |= COLLISION_PINS;
	
	/* Enable PC-int on pins (but no other)*/
	PCMSK = COLLISION_PINS;

	/* Enable PB-int */
	SETBIT(GIMSK,PCIE);
}