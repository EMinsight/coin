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
  \class SoMultipleCopy SoMultipleCopy.h Inventor/nodes/SoMultipleCopy.h
  \brief The SoMultipleCopy class ...
  \ingroup nodes

  FIXME: write class doc
*/

#include <Inventor/SbName.h>
#include <Inventor/nodes/SoMultipleCopy.h>
#include <Inventor/nodes/SoSubNode.h>

#if !defined(COIN_EXCLUDE_SOSTATE)
#include <Inventor/misc/SoState.h>
#endif // !COIN_EXCLUDE_SOSTATE

#if !defined(COIN_EXCLUDE_SOGETBOUNDINGBOXACTION)
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#endif // !COIN_EXCLUDE_SOGETBOUNDINGBOXACTION
#if !defined(COIN_EXCLUDE_SOGLRENDERACTION)
#include <Inventor/actions/SoGLRenderAction.h>
#endif // !COIN_EXCLUDE_SOGLRENDERACTION

#if !defined(COIN_EXCLUDE_SOMODELMATRIXELEMENT)
#include <Inventor/elements/SoModelMatrixElement.h>
#endif // !COIN_EXCLUDE_SOMODELMATRIXELEMENT
#if !defined(COIN_EXCLUDE_SOSWITCHELEMENT)
#include <Inventor/elements/SoSwitchElement.h>
#endif // !COIN_EXCLUDE_SOSWITCHELEMENT
#if !defined(COIN_EXCLUDE_SOBBOXMODELMATRIXELEMENT)
#include <Inventor/elements/SoBBoxModelMatrixElement.h>
#endif // !COIN_EXCLUDE_SOBBOXMODELMATRIXELEMENT

/*!
  \var SoMFMatrix SoMultipleCopy::matrix
  FIXME: write documentation for field
*/

// *************************************************************************

//$ BEGIN TEMPLATE NodeSource(SoMultipleCopy)
SoType SoMultipleCopy::classTypeId = SoType::badType();

/*!
  Returns a new instance of the SoMultipleCopy node class.
*/
void *
SoMultipleCopy::createInstance(void)
{
  return new SoMultipleCopy;
}

/*!
  Returns the unique type identifier for the SoMultipleCopy class.
*/
SoType
SoMultipleCopy::getClassTypeId(void)
{
  return SoMultipleCopy::classTypeId;
}

/*!
  Returns type identifier for an object.
*/
SoType
SoMultipleCopy::getTypeId(void) const
{
  return SoMultipleCopy::classTypeId;
}
//$ END TEMPLATE NodeSource

/*!
  Constructor.
*/
SoMultipleCopy::SoMultipleCopy()
{
//$ BEGIN TEMPLATE NodeConstructor(SoMultipleCopy)
  // Make sure the class has been initialized.
  assert(SoMultipleCopy::classTypeId != SoType::badType());
//$ END TEMPLATE NodeConstructor

  SO_NODE_ADD_FIELD(matrix, (SbMatrix(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1)));
}

/*!
  Destructor.
*/
SoMultipleCopy::~SoMultipleCopy()
{
}

/*!
  Does initialization common for all objects of the
  SoMultipleCopy class. This includes setting up the
  type system, among other things.
*/
void
SoMultipleCopy::initClass(void)
{
//$ BEGIN TEMPLATE InitNodeSource(MultipleCopy)
  // Make sure we only initialize once.
  assert(SoMultipleCopy::classTypeId == SoType::badType());
  // Make sure superclass get initialized before subclass.
  assert(inherited::getClassTypeId() != SoType::badType());

  SoMultipleCopy::classTypeId =
    SoType::createType(inherited::getClassTypeId(), "MultipleCopy",
                       &SoMultipleCopy::createInstance,
                       SoNode::nextActionMethodIndex++);
//$ END TEMPLATE InitNodeSource
}

/*!
  Clean out all statically allocated resources.
  This method is only useful for debugging purposes.
*/
void
SoMultipleCopy::cleanClass(void)
{
}

#if !defined(COIN_EXCLUDE_SOGETBOUNDINGBOXACTION)
/*!
  FIXME: write function documentation
*/
void
SoMultipleCopy::getBoundingBox(SoGetBoundingBoxAction * action)
{
  // store incoming modelmatrix
  SbMatrix mat = SoModelMatrixElement::get(action->getState());

  // get reference to the box
  SbXfBox3f & box = action->getXfBoundingBox();
 
  // store current bbox
  SbXfBox3f incomingbox = box;

  // accumulation variables
  SbVec3f acccenter(0.0f, 0.0f, 0.0f);
  int numCenters = 0;
  SbXfBox3f totalbox;

  for (int i=0; i < matrix.getNum(); i++) {
    action->getState()->push();

    SoSwitchElement::set(action->getState(), i);

    // make current box empty to calculate bbox of this separator
    box.makeEmpty();
    box.setTransform(SbMatrix::identity());
    
    // set bbox matrix
    SoBBoxModelMatrixElement::set(action->getState(), this, matrix[i]);
    
    // traverse all children, calculate the local bbox
    inherited::getBoundingBox(action);
    
    // If center point is set, accumulate center.
    if (action->isCenterSet()) {
      acccenter += action->getCenter();
      numCenters++;
      action->resetCenter();
    }

    // expand box by stored bbox
    if (!totalbox.isEmpty()) box.extendBy(totalbox);
    totalbox = box;

    action->getState()->pop();
  }

  // transform the local bbox by stored model matrix
  if (!box.isEmpty()) box.transform(mat);
  if (!incomingbox.isEmpty()) box.extendBy(incomingbox);

  if (numCenters != 0)
    action->setCenter(acccenter / numCenters, FALSE);
}
#endif // !COIN_EXCLUDE_SOGETBOUNDINGBOXACTION

#if !defined(COIN_EXCLUDE_SOGLRENDERACTION)
/*!
  FIXME: write function documentation
*/
void
SoMultipleCopy::GLRender(SoGLRenderAction * action)
{
  for (int i=0; i < matrix.getNum(); i++) {
    action->getState()->push();
    SoSwitchElement::set(action->getState(), i);
    SoModelMatrixElement::mult(action->getState(), this, matrix[i]);
    inherited::GLRender(action);
    action->getState()->pop();
  }
}
#endif // !COIN_EXCLUDE_SOGLRENDERACTION


/*!
  FIXME: write doc
 */
SbBool
SoMultipleCopy::affectsState(void) const
{
  assert(0 && "FIXME: not implemented");
  return TRUE;
}

#if !defined(COIN_EXCLUDE_SOACTION)
/*!
  FIXME: write doc
 */
void
SoMultipleCopy::doAction(SoAction * action)
{
  assert(0 && "FIXME: not implemented");
}
#endif // !COIN_EXCLUDE_SOACTION

#if !defined(COIN_EXCLUDE_SOCALLBACKACTION)
/*!
  FIXME: write doc
 */
void
SoMultipleCopy::callback(SoCallbackAction * action)
{
  assert(0 && "FIXME: not implemented");
}
#endif // !COIN_EXCLUDE_SOCALLBACKACTION

#if !defined(COIN_EXCLUDE_SOPICKACTION)
/*!
  FIXME: write doc
 */
void
SoMultipleCopy::pick(SoPickAction * action)
{
  assert(0 && "FIXME: not implemented");
}
#endif // !COIN_EXCLUDE_SOPICKACTION

#if !defined(COIN_EXCLUDE_SOHANDLEEVENTACTION)
/*!
  FIXME: write doc
 */
void
SoMultipleCopy::handleEvent(SoHandleEventAction * action)
{
  assert(0 && "FIXME: not implemented");
}
#endif // !COIN_EXCLUDE_SOHANDLEEVENTACTION

#if !defined(COIN_EXCLUDE_SOGETMATRIXACTION)
/*!
  FIXME: write doc
 */
void
SoMultipleCopy::getMatrix(SoGetMatrixAction * action)
{
  assert(0 && "FIXME: not implemented");
}
#endif // !COIN_EXCLUDE_SOGETMATRIXACTION

#if !defined(COIN_EXCLUDE_SOSEARCHACTION)
/*!
  FIXME: write doc
 */
void
SoMultipleCopy::search(SoSearchAction * action)
{
  assert(0 && "FIXME: not implemented");
}
#endif // !COIN_EXCLUDE_SOSEARCHACTION

#if !defined(COIN_EXCLUDE_SOGETPRIMITIVECOUNTACTION)
/*!
  FIXME: write doc
 */
void
SoMultipleCopy::getPrimitiveCount(SoGetPrimitiveCountAction * action)
{
  assert(0 && "FIXME: not implemented");
}
#endif // !COIN_EXCLUDE_SOGETPRIMITIVECOUNTACTION
