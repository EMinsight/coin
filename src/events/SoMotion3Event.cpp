/**************************************************************************\
 *
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
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
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
\**************************************************************************/

/*!
  \class SoMotion3Event SoMotion3Event.h Inventor/events/SoMotion3Event.h
  \brief The SoMotion3Event class contains information about 3D movement
  events.
  \ingroup events

  Motion3 events are generated by devices capable of "3D motion", for
  instance spaceballs. Instances of this class contains information about
  these devices' translations and rotations in all 3 dimensions.

  \sa SoEvent, SoLocation2Event
  \sa SoEventCallback, SoHandleEventAction */

#include <Inventor/events/SoMotion3Event.h>
#include <assert.h>


//$ BEGIN TEMPLATE EventSource(SoMotion3Event)
/*!
  \var SoMotion3Event::classTypeId
  Unique type identification for the SoMotion3Event class type.
*/
SoType SoMotion3Event::classTypeId = SoType::badType();

/*!
  This is a virtual function overloaded in all subclasses which will
  return the type identificator of the class instance.

  \sa getClassTypeId(), isOfType()
*/
SoType
SoMotion3Event::getTypeId(void) const
{
  return SoMotion3Event::classTypeId;
}

/*!
  Returns the type identificator for the SoMotion3Event class.

  \sa getTypeId(), isOfType()
*/
SoType
SoMotion3Event::getClassTypeId(void)
{
  return SoMotion3Event::classTypeId;
}
//$ END TEMPLATE EventSource

/*!
  Initialize the type information data.
 */
void
SoMotion3Event::initClass(void)
{
//$ BEGIN TEMPLATE EventInitClass(Motion3Event)
  // Make sure we only initialize once.
  assert(SoMotion3Event::classTypeId == SoType::badType());
  // Make sure superclass get initialized before subclass.
  assert(inherited::getClassTypeId() != SoType::badType());

  SoMotion3Event::classTypeId =
    SoType::createType(inherited::getClassTypeId(), "Motion3Event");
//$ END TEMPLATE EventInitClass
}

/*!
  Constructor. Resets values for translation and rotation information.
 */
SoMotion3Event::SoMotion3Event(void)
{
  this->translation.setValue(0.0f, 0.0f, 0.0f);
  this->rotation = SbRotation::identity();
}

/*!
  Destructor.
 */
SoMotion3Event::~SoMotion3Event()
{
}

/*!
  Sets the translation value of this event. Method is used by the
  window specific device class(es) generating the event.

  \sa getTranslation()
 */
void
SoMotion3Event::setTranslation(const SbVec3f & t)
{
  this->translation = t;
}

/*!
  Returns translation value. Note that translation are specified relative
  to former events, i.e. the values given here are \e not accumulated
  global coordinates.

  \sa getTime()
 */
const SbVec3f &
SoMotion3Event::getTranslation(void) const
{
  return this->translation;
}

/*!
  Sets the rotation value of this event. Method is used by the
  window specific device class(es) generating the event.
 */
void
SoMotion3Event::setRotation(const SbRotation & r)
{
  this->rotation = r;
}

/*!
  Returns rotational value. Note that rotations are specified relative
  to former events, i.e. the values given here are \e not accumulated
  rotations.

  \sa getTime()
 */
const SbRotation &
SoMotion3Event::getRotation(void) const
{
  return this->rotation;
}
