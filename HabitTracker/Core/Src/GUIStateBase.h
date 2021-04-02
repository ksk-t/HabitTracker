/*
 * GUIStateBase.h
 *
 *  Created on: Mar 30, 2021
 *      Author: keisu
 */

#ifndef SRC_GUISTATEBASE_H_
#define SRC_GUISTATEBASE_H_

#include "GraphicsEngine.h"

class GUIController; // Forward declaration

class GUIStateBase
{
public:
	GUIStateBase(GraphicsEngine* gfx_engine, GUIController* controller) : m_gfx_engine(gfx_engine), m_controller(controller) {};
	virtual void UILeft(){};
	virtual void UIRight(){};
	virtual void UISelect(){};
	virtual void UIDraw(){};
	virtual void OnLoaded(){};
	virtual ~GUIStateBase() {};
protected:
	GraphicsEngine* m_gfx_engine;
	GUIController* m_controller;
};



#endif /* SRC_GUISTATEBASE_H_ */
