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
  \class SoLocation2Event SoLocation2Event.h Inventor/events/SoLocation2Event.h
  \brief The SoLocation2Event class contains information about 2D movement
  events.
  \ingroup events

  Location2 events are generated by devices capable of 2D, e.g. pointer
  devices -- typically computer mice. Instances of this class contains
  information about the position of the pointer on the render area.

  SoLocation2Event does not contain any new information versus its
  superclass, its sole purpose is to make it possible to specify the
  type of the event for event object receivers in the scene graph.

  \sa SoEvent, SoMotion3Event
  \sa SoEventCallback, SoHandleEventAction */

#include <Inventor/events/SoLocation2Event.h>
#include <assert.h>


//$ BEGIN TEMPLATE EventSource(SoLocation2Event)
/*!
  \var SoLocation2Event::classTypeId
  Unique type identification for the SoLocation2Event class type.
*/
SoType SoLocation2Event::classTypeId = SoType::badType();

/*!
  This is a virtual function overloaded in all subclasses which will
  return the type identificator of the class instance.

  \sa getClassTypeId(), isOfType()
*/
SoType
SoLocation2Event::getTypeId(void) const
{
  return SoLocation2Event::classTypeId;
}

/*!
  Returns the type identificator for the SoLocation2Event class.

  \sa getTypeId(), isOfType()
*/
SoType
SoLocation2Event::getClassTypeId(void)
{
  return SoLocation2Event::classTypeId;
}
//$ END TEMPLATE EventSource

/*!
  Initialize the type information data.
 */
void
SoLocation2Event::initClass(void)
{
//$ BEGIN TEMPLATE EventInitClass(Location2Event)
  // Make sure we only initialize once.
  assert(SoLocation2Event::classTypeId == SoType::badType());
  // Make sure superclass get initialized before subclass.
  assert(inherited::getClassTypeId() != SoType::badType());

  SoLocation2Event::classTypeId =
    SoType::createType(inherited::getClassTypeId(), "Location2Event");
//$ END TEMPLATE EventInitClass
}

/*!
  Destructor.
 */
SoLocation2Event::~SoLocation2Event()
{
}
