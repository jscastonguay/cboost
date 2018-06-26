/* 
 * File:   general.h
 * Author: Proprietaire
 *
 * Created on June 18, 2018, 12:10 PM
 */

#ifndef GENERAL_H
#define	GENERAL_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef UNIT_TEST
#define STATIC
#else
#define STATIC static
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* GENERAL_H */

