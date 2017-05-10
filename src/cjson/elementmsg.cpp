/*
 * =====================================================================================
 *
 *       Filename:  elementmsg.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年05月02日 18时02分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kevin (WangWei), kevin.wang2004@hotmail.com
 *        Company:  LiLin-Tech
 *   Organization:  GNU
 *
 * =====================================================================================
 */

#include "elementmsg.h"

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Elementmsg
 * Description:  
 *--------------------------------------------------------------------------------------
 */
Elementmsg::Elementmsg ()
{
}  /* -----  end of method Elementmsg::Elementmsg  (constructor)  ----- */

Elementmsg::~Elementmsg ()
{
}  /* -----  end of method Elementmsg::Elementmsg  (destructor)  ----- */

int Elementmsg::save_a_element(ABOOK* point)
{
	INTERNAL_ABOOK tmpe;
	tmpe.name  	 = std::string(point->name);
	tmpe.email 	 = std::string(point->email);
	tmpe.description = std::string(point->description);

	m_vector.push_back(tmpe);
	return 0;
}

int Elementmsg::load_a_element(ABOOK* point,int index)
{
	strcpy(point->name,m_vector[index].name.c_str());
	strcpy(point->email,m_vector[index].email.c_str());
	strcpy(point->description,m_vector[index].description.c_str());

	return 0;
}

size_t Elementmsg::getAccount()
{
	if ( m_vector.empty() )
		return 0;
	else return m_vector.size();
}
