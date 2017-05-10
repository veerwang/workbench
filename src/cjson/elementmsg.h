/*
 * =====================================================================================
 *
 *       Filename:  elementmsg.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年05月02日 18时01分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kevin (WangWei), kevin.wang2004@hotmail.com
 *        Company:  LiLin-Tech
 *   Organization:  GNU
 *
 * =====================================================================================
 */

#include <vector>
#include <string>
#include "../calcurse.h"

/*
 * =====================================================================================
 *        Class:  Elementmsg
 *  Description:  
 * =====================================================================================
 */
class Elementmsg
{
	public:
		/* ====================  LIFECYCLE     ======================================= */
		Elementmsg ();                                       /* constructor */
		~Elementmsg ();                                      /* destructor  */

		/* ====================  ACCESSORS     ======================================= */
		/* ABook struct */
		typedef struct _ABOOK {
			std::string name;		 /* 联系人姓名 */
			std::string email;		 /* 联系人E-mail地址 */
			std::string description;         /* 描述信息 */
		} INTERNAL_ABOOK;

		int save_a_element(ABOOK* point);
		int load_a_element(ABOOK* point,int index);
		size_t getAccount();
		/* ====================  MUTATORS      ======================================= */

		/* ====================  OPERATORS     ======================================= */

	protected:
		/* ====================  DATA MEMBERS  ======================================= */

	private:
		/* ====================  DATA MEMBERS  ======================================= */
		std::vector<INTERNAL_ABOOK>	m_vector;

}; /* -----  end of class Elementmsg  ----- */

