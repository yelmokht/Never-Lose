/*******************************************************************************
* File Name: SM_2.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_SM_2_H) /* Pins SM_2_H */
#define CY_PINS_SM_2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SM_2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SM_2__PORT == 15 && ((SM_2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SM_2_Write(uint8 value);
void    SM_2_SetDriveMode(uint8 mode);
uint8   SM_2_ReadDataReg(void);
uint8   SM_2_Read(void);
void    SM_2_SetInterruptMode(uint16 position, uint16 mode);
uint8   SM_2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SM_2_SetDriveMode() function.
     *  @{
     */
        #define SM_2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SM_2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SM_2_DM_RES_UP          PIN_DM_RES_UP
        #define SM_2_DM_RES_DWN         PIN_DM_RES_DWN
        #define SM_2_DM_OD_LO           PIN_DM_OD_LO
        #define SM_2_DM_OD_HI           PIN_DM_OD_HI
        #define SM_2_DM_STRONG          PIN_DM_STRONG
        #define SM_2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SM_2_MASK               SM_2__MASK
#define SM_2_SHIFT              SM_2__SHIFT
#define SM_2_WIDTH              1u

/* Interrupt constants */
#if defined(SM_2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SM_2_SetInterruptMode() function.
     *  @{
     */
        #define SM_2_INTR_NONE      (uint16)(0x0000u)
        #define SM_2_INTR_RISING    (uint16)(0x0001u)
        #define SM_2_INTR_FALLING   (uint16)(0x0002u)
        #define SM_2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SM_2_INTR_MASK      (0x01u) 
#endif /* (SM_2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SM_2_PS                     (* (reg8 *) SM_2__PS)
/* Data Register */
#define SM_2_DR                     (* (reg8 *) SM_2__DR)
/* Port Number */
#define SM_2_PRT_NUM                (* (reg8 *) SM_2__PRT) 
/* Connect to Analog Globals */                                                  
#define SM_2_AG                     (* (reg8 *) SM_2__AG)                       
/* Analog MUX bux enable */
#define SM_2_AMUX                   (* (reg8 *) SM_2__AMUX) 
/* Bidirectional Enable */                                                        
#define SM_2_BIE                    (* (reg8 *) SM_2__BIE)
/* Bit-mask for Aliased Register Access */
#define SM_2_BIT_MASK               (* (reg8 *) SM_2__BIT_MASK)
/* Bypass Enable */
#define SM_2_BYP                    (* (reg8 *) SM_2__BYP)
/* Port wide control signals */                                                   
#define SM_2_CTL                    (* (reg8 *) SM_2__CTL)
/* Drive Modes */
#define SM_2_DM0                    (* (reg8 *) SM_2__DM0) 
#define SM_2_DM1                    (* (reg8 *) SM_2__DM1)
#define SM_2_DM2                    (* (reg8 *) SM_2__DM2) 
/* Input Buffer Disable Override */
#define SM_2_INP_DIS                (* (reg8 *) SM_2__INP_DIS)
/* LCD Common or Segment Drive */
#define SM_2_LCD_COM_SEG            (* (reg8 *) SM_2__LCD_COM_SEG)
/* Enable Segment LCD */
#define SM_2_LCD_EN                 (* (reg8 *) SM_2__LCD_EN)
/* Slew Rate Control */
#define SM_2_SLW                    (* (reg8 *) SM_2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SM_2_PRTDSI__CAPS_SEL       (* (reg8 *) SM_2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SM_2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SM_2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SM_2_PRTDSI__OE_SEL0        (* (reg8 *) SM_2__PRTDSI__OE_SEL0) 
#define SM_2_PRTDSI__OE_SEL1        (* (reg8 *) SM_2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SM_2_PRTDSI__OUT_SEL0       (* (reg8 *) SM_2__PRTDSI__OUT_SEL0) 
#define SM_2_PRTDSI__OUT_SEL1       (* (reg8 *) SM_2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SM_2_PRTDSI__SYNC_OUT       (* (reg8 *) SM_2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SM_2__SIO_CFG)
    #define SM_2_SIO_HYST_EN        (* (reg8 *) SM_2__SIO_HYST_EN)
    #define SM_2_SIO_REG_HIFREQ     (* (reg8 *) SM_2__SIO_REG_HIFREQ)
    #define SM_2_SIO_CFG            (* (reg8 *) SM_2__SIO_CFG)
    #define SM_2_SIO_DIFF           (* (reg8 *) SM_2__SIO_DIFF)
#endif /* (SM_2__SIO_CFG) */

/* Interrupt Registers */
#if defined(SM_2__INTSTAT)
    #define SM_2_INTSTAT            (* (reg8 *) SM_2__INTSTAT)
    #define SM_2_SNAP               (* (reg8 *) SM_2__SNAP)
    
	#define SM_2_0_INTTYPE_REG 		(* (reg8 *) SM_2__0__INTTYPE)
#endif /* (SM_2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SM_2_H */


/* [] END OF FILE */
