/**************************************************************************\
 * 
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 73540378 Fax: +47 73943861
 *
\**************************************************************************/

/*!
  \class SoLevelOfSimplification SoLevelOfSimplification.h Inventor/nodes/SoLevelOfSimplification.h
  \brief The SoLevelOfSimplification class ...
  \ingroup nodes

  FIXME: write class doc
*/

#include <Inventor/SbName.h>
#include <Inventor/nodes/SoLevelOfSimplification.h>
#include <Inventor/nodes/SoSubNode.h>

#if !defined(COIN_EXCLUDE_SOGETBOUNDINGBOXACTION)
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#endif // !COIN_EXCLUDE_SOGETBOUNDINGBOXACTION

#if !defined(COIN_EXCLUDE_SODECIMATIONTYPEELEMENT)
#include <Inventor/elements/SoDecimationTypeElement.h>
#endif // !COIN_EXCLUDE_SODECIMATIONTYPEELEMENT
#if !defined(COIN_EXCLUDE_SODECIMATIONPERCENTAGEELEMENT)
#include <Inventor/elements/SoDecimationPercentageElement.h>
#endif // !COIN_EXCLUDE_SODECIMATIONPERCENTAGEELEMENT

/*!
  \var SoMFFloat SoLevelOfSimplification::percentages
  FIXME: write documentation for field
*/
/*!
  \var SoSFInt32 SoLevelOfSimplification::numTriangles
  FIXME: write documentation for field
*/

// *************************************************************************

//$ BEGIN TEMPLATE NodeSource(SoLevelOfSimplification)
SoType SoLevelOfSimplification::classTypeId = SoType::badType();

/*!
  Returns a new instance of the SoLevelOfSimplification node class.
*/
void *
SoLevelOfSimplification::createInstance(void)
{
  return new SoLevelOfSimplification;
}

/*!
  Returns the unique type identifier for the SoLevelOfSimplification class.
*/
SoType
SoLevelOfSimplification::getClassTypeId(void)
{
  return SoLevelOfSimplification::classTypeId;
}

/*!
  Returns type identifier for an object.
*/
SoType
SoLevelOfSimplification::getTypeId(void) const
{
  return SoLevelOfSimplification::classTypeId;
}
//$ END TEMPLATE NodeSource

/*!
  Constructor.
*/
SoLevelOfSimplification::SoLevelOfSimplification()
{
//$ BEGIN TEMPLATE NodeConstructor(SoLevelOfSimplification)
  // Make sure the class has been initialized.
  assert(SoLevelOfSimplification::classTypeId != SoType::badType());
//$ END TEMPLATE NodeConstructor

  SO_NODE_ADD_FIELD(percentages, (0.0f));
  // FIXME: is this the correct way of making an empty multifield?
  // 19990301 mortene.
  percentages.setNum(0);

  SO_NODE_ADD_FIELD(numTriangles, (-1));
}

/*!
  Destructor.
*/
SoLevelOfSimplification::~SoLevelOfSimplification()
{
}

/*!
  Does initialization common for all objects of the
  SoLevelOfSimplification class. This includes setting up the
  type system, among other things.
*/
void
SoLevelOfSimplification::initClass(void)
{
//$ BEGIN TEMPLATE InitNodeSource(LevelOfSimplification)
  // Make sure we only initialize once.
  assert(SoLevelOfSimplification::classTypeId == SoType::badType());
  // Make sure superclass get initialized before subclass.
  assert(inherited::getClassTypeId() != SoType::badType());

  SoLevelOfSimplification::classTypeId =
    SoType::createType(inherited::getClassTypeId(), "LevelOfSimplification",
                       &SoLevelOfSimplification::createInstance,
                       SoNode::nextActionMethodIndex++);
//$ END TEMPLATE InitNodeSource

#if !defined(COIN_EXCLUDE_SOGETBOUNDINGBOXACTION)
  SO_ENABLE(SoGetBoundingBoxAction, SoDecimationTypeElement);
  SO_ENABLE(SoGetBoundingBoxAction, SoDecimationPercentageElement);
#endif // !COIN_EXCLUDE_SOGETBOUNDINGBOXACTION
}

/*!
  Clean out all statically allocated resources.
  This method is only useful for debugging purposes.
*/
void
SoLevelOfSimplification::cleanClass(void)
{
}


#if !defined(COIN_EXCLUDE_SOGETPRIMITIVECOUNTACTION)
/*!
  FIXME: write doc
 */
void
SoLevelOfSimplification::getPrimitiveCount(SoGetPrimitiveCountAction * action)
{
  assert(0 && "FIXME: not implemented");
}
#endif // !COIN_EXCLUDE_SOGETPRIMITIVECOUNTACTION

#if !defined(COIN_EXCLUDE_SOACTION)
/*!
  FIXME: write doc
 */
int
SoLevelOfSimplification::whichToTraverse(SoAction *)
{
  assert(0 && "FIXME: not implemented");
  return 0;
}
#endif // !COIN_EXCLUDE_SOACTION
