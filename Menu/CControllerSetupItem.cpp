
#include "CControllerSetupItem.h"
#include "Defines.h"
#include "CToggleItem.h"
#include "../CApplication.h"
#include "../Engine/CInputManager.h"
#include "../Engine/CMeshManager.h"
#include "../Engine/CTextureManager.h"
#include "../Engine/CTextDrawer.h"
#include "../Engine/intToString.h"
#include "../Engine/ortho.h"

CControllerSetupItem::CControllerSetupItem(int value): CToggleItem(" ")
{
	addOption("i,j,k,l,u",0);
	addOption("Arrow Keys",1);
	addOption("w,a,s,d,q",2);
	addOption("g,v,b,n,f",3);


	// are there joysticks present ?
	if (CApplication::m_pInputManager->joysticksPresent())
	{
		string joystickString("Joystick ");

		//if so add them to the menu item
		for (int i = 0; i < CApplication::m_pInputManager->getJoystickCount(); i++)
		{
			string tmp = joystickString + convertValueToString(i+1);
			addOption(tmp.c_str(),i+4);
//			addOption("blah",i+4);
		}
	
	}
	
	
	if (value > 3) // Greater 3 - This must be a joystick!
	{
		// is this joystick present ?
		if (CApplication::m_pInputManager->isJoystickPresent(value-4))
			setValue(value);
		else
			setValue(3);
	}
	else
		// no Joystick. keyboard is always present. no further check necessary
		setValue(value);
		
	determineTexture();
}

void CControllerSetupItem::determineTexture()
{
	switch((*m_itIterator).value)
	{
		case 0:
			m_iCurrentTexture = KEYBOARD_IJKL_TEXTURE;
			break;
		case 1:
			m_iCurrentTexture = KEYBOARD_ARROWS_TEXTURE;
			break;
		case 2:
			m_iCurrentTexture = KEYBOARD_WASD_TEXTURE;
			break;
		case 3:
			m_iCurrentTexture = KEYBOARD_FCVB_TEXTURE;
			break;
		default:
			//m_iCurrentTexture = KEYBOARD_FCVB_TEXTURE;
			m_iCurrentTexture = JOYSTICK_TEXTURE;
	}	
	
}
/*
void CControllerSetupItem::drawQuad()
{
	glPushMatrix();
	glTranslatef(m_vPosition.x-20,m_vPosition.y, m_vPosition.z);
	glBegin(GL_QUADS);
		glVertex3f(30,30,0);
		glVertex3f(-30,30,0);
		glVertex3f(-30,-30,0);
		glVertex3f(30,-30,0);
	glEnd();
	glPopMatrix();	
}*/


void CControllerSetupItem::draw()
{
	if (m_bActive)
	{
		determineTexture();
	//	glColor3f(1,0,0);
	}
	//else
	//	glColor3f(1,1,1);
	
	if (m_bActive) drawQuad();
	
	glPushMatrix();
		glTranslatef(relToAbs(m_vPosition.x,0),relToAbs(m_vPosition.y,1), -1);
		glPushMatrix();
			glTranslatef(0,50, -1);
			glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
			glEnable( GL_BLEND );
	//		glColor3f(1,1,1);
			CApplication::m_pTextureManager->bindTexture(m_iCurrentTexture);
			glScalef(150,150,150);
			glBegin(GL_QUADS);
/*				 glTexCoord2f(1,1);glVertex3f(100,25,0);
				 glTexCoord2f(0,1);glVertex3f(0,25,0); 
				 glTexCoord2f(0,0);glVertex3f(0,-25,0);
				 glTexCoord2f(1,0);glVertex3f(100,-25,0);*/
				glTexCoord2f(1,1);glVertex3f(1,0.25,0);
				glTexCoord2f(0,1);glVertex3f(0,0.25,0); 
				glTexCoord2f(0,0);glVertex3f(0,-0.25,0);
				glTexCoord2f(1,0);glVertex3f(1,-0.25,0);
			glEnd();
			glDisable(GL_BLEND);
			
		glPopMatrix();
	//	CApplication::m_pTextDrawer->setSize(24);
		glBindTexture(GL_TEXTURE_2D,NULL);
		CApplication::m_pTextDrawer->drawText(0,0,(*m_itIterator).name);
	glPopMatrix();
	
	m_bActive = false;
	//glColor3f(1,1,1);
	
}

