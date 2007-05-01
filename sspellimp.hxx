/*************************************************************************
 *
 *  Authors:
 *  Sun Microsystems Inc., October, 2000
 *  Pasi Ryhänen, 2002/05/23
 *  Harri Pitkänen (hatapitk@iki.fi), 2005
 *
 *  The Contents of this file are made available subject to the terms of
 *  GNU Lesser General Public License Version 2.1
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA  02110-1301, USA
 *
 ************************************************************************/

#ifndef _SSPELLIMP_HXX_
#define _SSPELLIMP_HXX_

#include <cppuhelper/implbase6.hxx>

#include <com/sun/star/lang/XComponent.hpp>
#include <com/sun/star/lang/XInitialization.hpp>
#include <com/sun/star/lang/XServiceDisplayName.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/beans/PropertyValues.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/linguistic2/XSpellChecker.hpp>
#include <com/sun/star/linguistic2/XSearchableDictionaryList.hpp>
#include <com/sun/star/linguistic2/XLinguServiceEventBroadcaster.hpp>

#include "sprophelp.hxx"
#include "lfmacros.hxx"
#include "lfimpl.hxx"
#include "XSpellAlternatives_impl.hxx"

using namespace ::rtl;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::linguistic2;

///////////////////////////////////////////////////////////////////////////

namespace LF_NAMESPACE {

class SpellChecker :
  public cppu::WeakImplHelper6
<
	XSpellChecker,
	XLinguServiceEventBroadcaster,
	XInitialization,
	XComponent,
	XServiceInfo,
	XServiceDisplayName >
{

  Sequence< Locale > aSuppLocales;
  ::cppu::OInterfaceContainerHelper aEvtListeners;
  Reference< XPropertyChangeListener > xPropHelper;
  PropertyHelper_Spell * pPropHelper;
  sal_Bool bDisposing;

  // disallow copy-constructor and assignment-operator for now
  SpellChecker(const SpellChecker &);
  SpellChecker & operator = (const SpellChecker &);

  PropertyHelper_Spell &	GetPropHelper_Impl();
  PropertyHelper_Spell &	GetPropHelper()
  {
    return pPropHelper ? *pPropHelper : GetPropHelper_Impl();
  }

  /*Reference< XSpellAlternatives >
  GetProposals( const OUString &rWord, const Locale &rLocale );*/


public:
  SpellChecker();
  virtual ~SpellChecker();

  // XSupportedLocales (for XSpellChecker)
  virtual Sequence< Locale > SAL_CALL 
  getLocales() 
    throw(RuntimeException);
  virtual sal_Bool SAL_CALL 
  hasLocale( const Locale& rLocale ) 
    throw(RuntimeException);

  // XSpellChecker
  virtual sal_Bool SAL_CALL 
  isValid( const OUString& rWord, const Locale& rLocale, 
	   const PropertyValues& rProperties ) 
    throw(IllegalArgumentException, 
	  RuntimeException);
  virtual Reference< XSpellAlternatives > SAL_CALL 
  spell( const OUString& rWord, const Locale& rLocale, 
	 const PropertyValues& rProperties ) 
    throw(IllegalArgumentException, 
	  RuntimeException);

  // XLinguServiceEventBroadcaster
  virtual sal_Bool SAL_CALL 
  addLinguServiceEventListener( 
			       const Reference< XLinguServiceEventListener >& rxLstnr ) 
    throw(RuntimeException);
  virtual sal_Bool SAL_CALL 
  removeLinguServiceEventListener( 
				  const Reference< XLinguServiceEventListener >& rxLstnr ) 
    throw(RuntimeException);
	
  // XServiceDisplayName
  virtual OUString SAL_CALL 
  getServiceDisplayName( const Locale& rLocale ) 
    throw(RuntimeException);

  // XInitialization
  virtual void SAL_CALL 
  initialize( const Sequence< Any >& rArguments ) 
    throw(Exception, RuntimeException);

  // XComponent
  virtual void SAL_CALL 
  dispose() 
    throw(RuntimeException);
  virtual void SAL_CALL 
  addEventListener( const Reference< XEventListener >& rxListener ) 
    throw(RuntimeException);
  virtual void SAL_CALL 
  removeEventListener( const Reference< XEventListener >& rxListener ) 
    throw(RuntimeException);

  ////////////////////////////////////////////////////////////
  // Service specific part
  //

  // XServiceInfo
  virtual OUString SAL_CALL 
  getImplementationName() 
    throw(RuntimeException);
  virtual sal_Bool SAL_CALL 
  supportsService( const OUString& rServiceName ) 
    throw(RuntimeException);
  virtual Sequence< OUString > SAL_CALL 
  getSupportedServiceNames() 
    throw(RuntimeException);


  static inline OUString	
  getImplementationName_Static() throw();
  static Sequence< OUString >	
  getSupportedServiceNames_Static();
};

inline OUString SpellChecker::getImplementationName_Static() throw() {
	return A2OU(MACROTOSTRING(LF_NAMESPACE)).concat(A2OU(".SpellChecker"));
}

}

///////////////////////////////////////////////////////////////////////////

#endif
