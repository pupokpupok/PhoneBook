
#include "ContactsService.hpp"

oatpp::Object<ContactsDto> ContactsService::createContacts(const oatpp::Object<ContactsDto>& dto) {

  auto dbResult = m_database->createContacts(dto);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<ContactsDto>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");
  return result[0];

}

oatpp::Object<ContactsDto> ContactsService::updateContacts(const oatpp::Object<ContactsDto>& dto) {

  auto dbResult = m_database->updateContacts(dto);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<ContactsDto>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");
  return result[0];

}

oatpp::Object<ContactsDto> ContactsService::getContactsById(const oatpp::Int32& id) {

  auto dbResult = m_database->getContactsById(id);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Contacts not found");

  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<ContactsDto>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

  return result[0];

}

oatpp::Object<PageDto<oatpp::Object<ContactsDto>>> ContactsService::getAllContacts(const oatpp::UInt32& offset, const oatpp::UInt32& limit) {

  oatpp::UInt32 countToFetch = limit;

  if(limit > 10) {
    countToFetch = 10;
  }

  auto dbResult = m_database->getAllContacts(offset, countToFetch);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<ContactsDto>>>();

  auto page = PageDto<oatpp::Object<ContactsDto>>::createShared();
  page->offset = offset;
  page->limit = countToFetch;
  page->count = items->size();
  page->items = items;

  return page;

}

oatpp::Object<StatusDto> ContactsService::deleteContactsById(const oatpp::Int32& id) {
  auto dbResult = m_database->deleteContactsById(id);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  auto status = StatusDto::createShared();
  status->status = "OK";
  status->code = 200;
  status->message = "User was successfully deleted";
  return status;
}