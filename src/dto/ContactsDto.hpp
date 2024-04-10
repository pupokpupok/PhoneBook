#ifndef ContactsDto_hpp
#define ContactsDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)


class ContactsDto : public oatpp::DTO {
  
  DTO_INIT(ContactsDto, DTO)

  DTO_FIELD(Int32, id, "id");
  DTO_FIELD(String, phone, "phone");
  DTO_FIELD(String, name, "name");
  DTO_FIELD(String, address, "address");

};

#include OATPP_CODEGEN_END(DTO)

#endif /* UserDto_hpp */
