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
  \class SoSpotLight SoSpotLight.h Inventor/nodes/SoSpotLight.h
  \brief The SoSpotLight class ...
  \ingroup nodes

  FIXME: write class doc
*/

#include <Inventor/SbName.h>
#include <Inventor/nodes/SoSpotLight.h>
#include <Inventor/nodes/SoSubNode.h>
#include <math.h>
#include <Inventor/SbColor4f.h>
#include <Inventor/SbVec4f.h>

#if COIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // COIN_DEBUG

#if !defined(COIN_EXCLUDE_SOGLRENDERACTION)
#include <Inventor/actions/SoGLRenderAction.h>
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32
#include <GL/gl.h>
#if !defined(COIN_EXCLUDE_SOGLLIGHTIDELEMENT)
#include <Inventor/elements/SoGLLightIdElement.h>
#endif // !COIN_EXCLUDE_SOGLLIGHTIDELEMENT
#endif // !COIN_EXCLUDE_SOGLRENDERACTION

#if !defined(COIN_EXCLUDE_SOENVIRONMENTELEMENT)
#include <Inventor/elements/SoEnvironmentElement.h>
#endif // ! COIN_EXCLUDE_SOENVIRONMENTELEMENT


/*!
  \var SoSFVec3f SoSpotLight::location
  FIXME: write documentation for field
*/
/*!
  \var SoSFVec3f SoSpotLight::direction
  FIXME: write documentation for field
*/
/*!
  \var SoSFFloat SoSpotLight::dropOffRate
  FIXME: write documentation for field
*/
/*!
  \var SoSFFloat SoSpotLight::cutOffAngle
  FIXME: write documentation for field
*/


// *************************************************************************

//$ BEGIN TEMPLATE NodeSource(SoSpotLight)
SoType SoSpotLight::classTypeId = SoType::badType();

/*!
  Returns a new instance of the SoSpotLight node class.
*/
void *
SoSpotLight::createInstance(void)
{
  return new SoSpotLight;
}

/*!
  Returns the unique type identifier for the SoSpotLight class.
*/
SoType
SoSpotLight::getClassTypeId(void)
{
  return SoSpotLight::classTypeId;
}

/*!
  Returns type identifier for an object.
*/
SoType
SoSpotLight::getTypeId(void) const
{
  return SoSpotLight::classTypeId;
}
//$ END TEMPLATE NodeSource

/*!
  Constructor.
*/
SoSpotLight::SoSpotLight()
{
//$ BEGIN TEMPLATE NodeConstructor(SoSpotLight)
  // Make sure the class has been initialized.
  assert(SoSpotLight::classTypeId != SoType::badType());
//$ END TEMPLATE NodeConstructor

  SO_NODE_ADD_FIELD(location, (SbVec3f(0.0f, 0.0f, 1.0f)));
  SO_NODE_ADD_FIELD(direction, (SbVec3f(0.0f, 0.0f, -1.0f)));
  SO_NODE_ADD_FIELD(dropOffRate, (0.0f));
  SO_NODE_ADD_FIELD(cutOffAngle, (M_PI/4.0f));
}

/*!
  Destructor.
*/
SoSpotLight::~SoSpotLight()
{
}

/*!
  Does initialization common for all objects of the
  SoSpotLight class. This includes setting up the
  type system, among other things.
*/
void
SoSpotLight::initClass(void)
{
//$ BEGIN TEMPLATE InitNodeSource(SpotLight)
  // Make sure we only initialize once.
  assert(SoSpotLight::classTypeId == SoType::badType());
  // Make sure superclass get initialized before subclass.
  assert(inherited::getClassTypeId() != SoType::badType());

  SoSpotLight::classTypeId =
    SoType::createType(inherited::getClassTypeId(), "SpotLight",
                       &SoSpotLight::createInstance,
                       SoNode::nextActionMethodIndex++);
//$ END TEMPLATE InitNodeSource
}

/*!
  Clean out all statically allocated resources.
  This method is only useful for debugging purposes.
*/
void
SoSpotLight::cleanClass(void)
{
}

#if !defined(COIN_EXCLUDE_SOGLRENDERACTION)
/*!
  FIXME: write function documentation
*/
void 
SoSpotLight::GLRender(SoGLRenderAction * action)
{
  if (!on.isIgnored() && !on.getValue()) return;

  SoState *state = action->getState();
  int idx = SoGLLightIdElement::increment(state);
  
  if (idx < 0) {
#if COIN_DEBUG
    SoDebugError::post("SoSpotLight::GLRender()",
		       "Max # lights exceeded :(\n");
#endif // COIN_DEBUG
    return;
  }

  GLenum light = (GLenum) (idx + GL_LIGHT0);

  SbColor4f lightcolor(0.0f, 0.0f, 0.0f, 1.0f);
  SbVec3f attenuation(0.0f, 0.0f, 1.0f);
#if !defined(COIN_EXCLUDE_SOENVIRONMENTELEMENT)
  lightcolor.setRGB(SoEnvironmentElement::getAmbientColor(state));      
  lightcolor *= SoEnvironmentElement::getAmbientIntensity(state);
  attenuation = SoEnvironmentElement::getLightAttenuation(state);
#endif // ! COIN_EXCLUDE_SOENVIRONMENTELEMENT

  glLightfv(light, GL_AMBIENT, lightcolor.getValue());
  glLightf(light, GL_QUADRATIC_ATTENUATION, attenuation[0]);
  glLightf(light, GL_LINEAR_ATTENUATION, attenuation[1]);
  glLightf(light, GL_CONSTANT_ATTENUATION, attenuation[2]);
  
  if (!color.isIgnored()) lightcolor.setRGB(color.getValue());
  else lightcolor.setRGB(SbColor(1.0f, 1.0f, 1.0f));
  if (!intensity.isIgnored()) lightcolor *= intensity.getValue();
  
  glLightfv(light, GL_DIFFUSE, lightcolor.getValue());
  glLightfv(light, GL_SPECULAR, lightcolor.getValue());
  
  SbVec3f loc(0.0f, 0.0f, 1.0f); // default
  if (!location.isIgnored()) loc = location.getValue();

  // point (or spot) light when w = 1.0
  SbVec4f posvec(loc[0], loc[1], loc[2], 1.0f);
  glLightfv(light, GL_POSITION, posvec.getValue());

  float cutOff = !cutOffAngle.isIgnored() ?
    cutOffAngle.getValue() * M_PI/180.0f :
    M_PI/4.0f;

  float dropOff = !dropOffRate.isIgnored() ?
    dropOffRate.getValue() * 128.0f :
    0.0f;
  
  glLightf(light, GL_SPOT_EXPONENT, dropOff);
  glLightf(light, GL_SPOT_CUTOFF, cutOff);
}
#endif // !COIN_EXCLUDE_SOGLRENDERACTION

