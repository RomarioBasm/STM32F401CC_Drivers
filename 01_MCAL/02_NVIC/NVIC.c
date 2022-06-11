#include "Std_types.h"

#include "NVIC.h"
#include "NVIC_cfg.h"
#include "NVIC_priv.h"

/******************** NVIC_enuEnableInterrupt ***************************
 * This function Enable an interrupt. ----------------------------------*
 * @param :  Copy_u8InterruptID (u8) : NVIC_INT_NUM_X  -> X : 0 -> 239 -*
 * @return: NVIC_enuErrorStatus ----------------------------------------*
 ************************************************************************/
NVIC_enuErrorStatus NVIC_enuEnableInterrupt(u8 Copy_u8InterruptID){

	NVIC_enuErrorStatus Ret_enuErrorStatus = NVIC_enuOK;

	/* VARIABLE TO GET REGISTER NUMBER */
    u8 Loc_u8Register;

    /* VARIABLE TO GET BIT NUMBER */
    u8 Loc_u8Bit;

    /* VALIDATION : CHECH INTERRUPT NUMBER */
	if(Copy_u8InterruptID > NVIC_INTERRUPTSNUMBER){
		Ret_enuErrorStatus = NVIC_enuErrorIntNumber;
	}

	else{

		/* GET BIT NUMBER */
		Loc_u8Bit = Copy_u8InterruptID % 32;

		/* GET REGISTER NUMBER */
		Loc_u8Register = Copy_u8InterruptID / 32;

		/* ENABLE THE INTERRUPT */
		NVIC_ISER_BASE[Loc_u8Register] |= (1<<Loc_u8Bit);

		Ret_enuErrorStatus = NVIC_enuOK;
	}



	return Ret_enuErrorStatus;
}

/******************** NVIC_enuDisableInterrupt **************************
 * This function Disable an interrupt. ---------------------------------*
 * @param :  Copy_u8InterruptID (u8) : NVIC_INT_NUM_X  -> X : 0 -> 239 -*
 * @return: NVIC_enuErrorStatus ----------------------------------------*
 ************************************************************************/
NVIC_enuErrorStatus NVIC_enuDisableInterrupt(u8 Copy_u8InterruptID){

	NVIC_enuErrorStatus Ret_enuErrorStatus = NVIC_enuOK;

	/* VARIABLE TO GET REGISTER NUMBER */
	u8 Loc_u8Register;

	/* VARIABLE TO GET BIT NUMBER */
	u8 Loc_u8Bit;

	/* VALIDATION : CHECH INTERRUPT NUMBER */
	if(Copy_u8InterruptID > NVIC_INTERRUPTSNUMBER){
		Ret_enuErrorStatus = NVIC_enuErrorIntNumber;
	}

	else{

		/* GET BIT NUMBER */
		Loc_u8Bit = Copy_u8InterruptID % 32;

		/* GET REGISTER NUMBER */
		Loc_u8Register = Copy_u8InterruptID / 32;

		/* ENABLE THE INTERRUPT */
		NVIC_ICER_BASE[Loc_u8Register] |= (1<<Loc_u8Bit);

		Ret_enuErrorStatus = NVIC_enuOK;
	}

	return Ret_enuErrorStatus;
}

/*********************** NVIC_enuSetPending *****************************
 * This function Set pending flag. -------------------------------------*
 * @param :  Copy_u8InterruptID (u8) : NVIC_INT_NUM_X  -> X : 0 -> 239 -*
 * @return: NVIC_enuErrorStatus ----------------------------------------*
 ************************************************************************/
NVIC_enuErrorStatus NVIC_enuSetPending(u8 Copy_u8InterruptID){

	NVIC_enuErrorStatus Ret_enuErrorStatus = NVIC_enuOK;

	/* VARIABLE TO GET REGISTER NUMBER */
	u8 Loc_u8Register;

	/* VARIABLE TO GET BIT NUMBER */
	u8 Loc_u8Bit;

	/* VALIDATION : CHECH INTERRUPT NUMBER */
	if(Copy_u8InterruptID > NVIC_INTERRUPTSNUMBER){
		Ret_enuErrorStatus = NVIC_enuErrorIntNumber;
	}

	else{

		/* GET BIT NUMBER */
		Loc_u8Bit = Copy_u8InterruptID % 32;

		/* GET REGISTER NUMBER */
		Loc_u8Register = Copy_u8InterruptID / 32;

		/* ENABLE THE INTERRUPT */
		NVIC_ISPR_BASE[Loc_u8Register] |= (1<<Loc_u8Bit);

		Ret_enuErrorStatus = NVIC_enuOK;
	}

	return Ret_enuErrorStatus;
}

/*********************** NVIC_enuClearPending ***************************
 * This function clear pending flag. -----------------------------------*
 * @param :  Copy_u8InterruptID (u8) : NVIC_INT_NUM_X  -> X : 0 -> 239 -*
 * @return: NVIC_enuErrorStatus ----------------------------------------*
 ************************************************************************/
NVIC_enuErrorStatus NVIC_enuClearPending(u8 Copy_u8InterruptID){

	NVIC_enuErrorStatus Ret_enuErrorStatus = NVIC_enuOK;

	/* VARIABLE TO GET REGISTER NUMBER */
	u8 Loc_u8Register;

	/* VARIABLE TO GET BIT NUMBER */
	u8 Loc_u8Bit;

	/* VALIDATION : CHECH INTERRUPT NUMBER */
	if(Copy_u8InterruptID > NVIC_INTERRUPTSNUMBER){
		Ret_enuErrorStatus = NVIC_enuErrorIntNumber;
	}

	else{

		/* GET BIT NUMBER */
		Loc_u8Bit = Copy_u8InterruptID % 32;

		/* GET REGISTER NUMBER */
		Loc_u8Register = Copy_u8InterruptID / 32;

		/* ENABLE THE INTERRUPT */
		NVIC_ICPR_BASE[Loc_u8Register] |= (1<<Loc_u8Bit);

		Ret_enuErrorStatus = NVIC_enuOK;
	}

	return Ret_enuErrorStatus;

}


/********************** NVIC_enuGetActiveStatus *************************
 * This function get active status  ------------------------------------*
 * @param :  Copy_u8InterruptID (u8) : NVIC_INT_NUM_X  -> X : 0 -> 239 -*
 *           Add_pu8ActiveValue(pu8) : to return the value -------------*
 * @return: NVIC_enuErrorStatus ----------------------------------------*
 ************************************************************************/
NVIC_enuErrorStatus NVIC_enuGetActiveStatus(u8 Copy_u8InterruptID, u8* Add_pu8ActiveValue){

	NVIC_enuErrorStatus Ret_enuErrorStatus = NVIC_enuOK;

	/* VARIABLE TO GET REGISTER NUMBER */
	u8 Loc_u8Register;

	/* VARIABLE TO GET BIT NUMBER */
	u8 Loc_u8Bit;

	/* VALIDATION : CHECH INTERRUPT NUMBER */
	if(Copy_u8InterruptID > NVIC_INTERRUPTSNUMBER){
		Ret_enuErrorStatus = NVIC_enuErrorIntNumber;
	}

	else{

		/* GET BIT NUMBER */
		Loc_u8Bit = Copy_u8InterruptID % 32;

		/* GET REGISTER NUMBER */
		Loc_u8Register = Copy_u8InterruptID / 32;

		/* ENABLE THE INTERRUPT */
		*Add_pu8ActiveValue = ((*(NVIC_IAB_BASE+Loc_u8Register))>>Loc_u8Bit) & 1;

		Ret_enuErrorStatus = NVIC_enuOK;
	}

	return Ret_enuErrorStatus;
}

NVIC_enuErrorStatus NVIC_enuSetSubPriority(u8 Copy_u8GroupPriority){
	NVIC_enuErrorStatus Ret_enuErrorStatus = NVIC_enuErrorGroupNumber;

	/* CHECKING THE INPUT ARGUMENT */
	if(Copy_u8GroupPriority >= SCB_PRI_GROUP_0 && Copy_u8GroupPriority <= SCB_PRI_GROUP_7 ){
		 Ret_enuErrorStatus = NVIC_enuOK;

		 /* SET THE GROUP PRIORITY */
		 SCB_AIRCR = Copy_u8GroupPriority;
	}

	return Ret_enuErrorStatus;
}

NVIC_enuErrorStatus NVIC_enuSetPriority(u8 Copy_u8InterruptID, u8 Copy_u8Priority){
	NVIC_enuErrorStatus Ret_enuErrorStatus = NVIC_enuOK;

	/* VARIABLE TO GET REGISTER NUMBER */
	u8 Loc_u8Register;

	/* VARIABLE TO GET BIT NUMBER */
	u8 Loc_u8Bit;

	/* VALIDATION : CHECH INTERRUPT NUMBER */
	if(Copy_u8InterruptID > NVIC_INTERRUPTSNUMBER){
		Ret_enuErrorStatus = NVIC_enuErrorIntNumber;
	}

	else{

		/* GET REGISTER NUMBER */
		Loc_u8Register = Copy_u8InterruptID / 4;

		/* GET BIT NUMBER */
		Loc_u8Bit = Copy_u8InterruptID % 4;

		/* SET THE PRIORITY */
		NVIC_IPR_BASE[Loc_u8Register] |= Copy_u8Priority;

		Ret_enuErrorStatus = NVIC_enuOK;
	}

	return Ret_enuErrorStatus;
}

NVIC_enuErrorStatus NVIC_enuEncodePriority(u8 Copy_u8GroupPriority, u8 Copy_u8SubPriority, u8 Copy_32PriGroup, u8* Add_pu8EncodedValue){

	NVIC_enuErrorStatus Ret_enuErrorStatus = NVIC_enuOK;
	u8 Loc_u8EncodedValue = 0;

	/* GET THE PRIORITY AS A NUMBER  0->7 */
	u8 Loc_u8PriorityGroup = (Copy_32PriGroup-SCB_PRI_GROUP_0)/256;

	if(!((Copy_32PriGroup>=SCB_PRI_GROUP_0) && (Copy_32PriGroup<=SCB_PRI_GROUP_7))){
		Ret_enuErrorStatus = NVIC_enuErrorGroupNumber;
	}

	else if(Add_pu8EncodedValue == ((void*)0)){
		Ret_enuErrorStatus = NVIC_enuErrorNullPointer;
	}

	else{

		/* SET GROUP PRIORITY */
		Loc_u8EncodedValue |= (Copy_u8SubPriority << (Loc_u8PriorityGroup));

		/* SET SUB PRIORITY */
		Loc_u8EncodedValue |= (Copy_u8SubPriority << (8 - NVIC_PRIORITY_BITS));

		*Add_pu8EncodedValue = Loc_u8EncodedValue;
	}

	return Ret_enuErrorStatus;
}
