
#ifndef EXAMPLE_POSTGRESQL_USERSERVICE_HPP
#define EXAMPLE_POSTGRESQL_USERSERVICE_HPP

#include "db/ContactsDb.hpp"
#include "dto/PageDto.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class ContactsService {
private:
  typedef oatpp::web::protocol::http::Status Status;
private:
  OATPP_COMPONENT(std::shared_ptr<ContactsDb>, m_database); // Inject database component
public:

  oatpp::Object<ContactsDto> createContacts(const oatpp::Object<ContactsDto>& dto);
  oatpp::Object<ContactsDto> updateContacts(const oatpp::Object<ContactsDto>& dto);
  oatpp::Object<ContactsDto> getContactsById(const oatpp::Int32& id);
  oatpp::Object<PageDto<oatpp::Object<ContactsDto>>> getAllContacts(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
  oatpp::Object<StatusDto> deleteContactsById(const oatpp::Int32& id);

};

#endif //EXAMPLE_POSTGRESQL_USERSERVICE_HPP
