//
//  Rooms.cpp
//  SimpleDB
//
//  Created by Александр Авершин on 07.03.2022.
//

#include "Rooms.h"

std::ostream& operator<< (std::ostream& out, const Room& st){// output. change ',' on ':' for better readability
    out << st.ID << ": "<< st.date << ", " << st.Price << ", "
        << st.Number << ", " << st.Floor << ", " << st.Area << ", " << st.Adress << std::endl;
    return out;
}
