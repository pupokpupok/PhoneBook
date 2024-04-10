
#ifndef UserController_hpp
#define UserController_hpp

#include "service/ContactsService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * User REST controller.
 */
class UserController : public oatpp::web::server::api::ApiController {
public:
  UserController(const std::shared_ptr<ObjectMapper>& objectMapper)
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
private:
  ContactsService m_contactsService; // Create user service.
public:

  static std::shared_ptr<UserController> createShared(
    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
  ){
    return std::make_shared<UserController>(objectMapper);
  }
  
  ENDPOINT_INFO(createContacts) {
    info->summary = "Create new Contacts";

    info->addConsumes<Object<ContactsDto>>("application/json");

    info->addResponse<Object<ContactsDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("POST", "contacts", createContacts,
           BODY_DTO(Object<ContactsDto>, contactsDto))
  {
    return createDtoResponse(Status::CODE_200, m_contactsService.createContacts(contactsDto));
  }
  
  
  ENDPOINT_INFO(putContacts) {
    info->summary = "Update contacts by contactsId";

    info->addConsumes<Object<ContactsDto>>("application/json");

    info->addResponse<Object<ContactsDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["contactsId"].description = "Contacts Identifier";
  }
  ENDPOINT("PUT", "contacts/{id}", putContacts,
           PATH(Int32, id),
           BODY_DTO(Object<ContactsDto>, contactsDto))
  {
    contactsDto->id = id;
    return createDtoResponse(Status::CODE_200, m_contactsService.updateContacts(contactsDto));
  }
  
  
  ENDPOINT_INFO(getContactsById) {
    info->summary = "Get one Contacts by userId";

    info->addResponse<Object<ContactsDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["id"].description = "Contacts Identifier";
  }
  ENDPOINT("GET", "contacts/{id}", getContactsById,
           PATH(Int32, id))
  {
    return createDtoResponse(Status::CODE_200, m_contactsService.getContactsById(id));
  }
  
  
  ENDPOINT_INFO(getContacts) {
    info->summary = "get all stored contacts";

    info->addResponse<oatpp::Object<ContactsDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET", "contacts/offset/{offset}/limit/{limit}", getContacts,
           PATH(UInt32, offset),
           PATH(UInt32, limit))
  {
    return createDtoResponse(Status::CODE_200, m_contactsService.getAllContacts(offset, limit));
  }
  
  
  ENDPOINT_INFO(deleteContacts) {
    info->summary = "Delete Contacts by id";

    info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["id"].description = "User Identifier";
  }
  ENDPOINT("DELETE", "contacts/{id}", deleteContacts,
           PATH(Int32, id))
  {
    return createDtoResponse(Status::CODE_200, m_contactsService.deleteContactsById(id));
  }

};

#include OATPP_CODEGEN_BEGIN(ApiController) //<- End Codegen

#endif /* UserController_hpp */
