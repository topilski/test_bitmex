/**
 * BitMEX API
 * ## REST API for the BitMEX Trading Platform  [View Changelog](/app/apiChangelog)    #### Getting Started  Base URI: [https://www.bitmex.com/api/v1](/api/v1)  ##### Fetching Data  All REST endpoints are documented below. You can try out any query right from this interface.  Most table queries accept `count`, `start`, and `reverse` params. Set `reverse=true` to get rows newest-first.  Additional documentation regarding filters, timestamps, and authentication is available in [the main API documentation](/app/restAPI).  *All* table data is available via the [Websocket](/app/wsAPI). We highly recommend using the socket if you want to have the quickest possible data without being subject to ratelimits.  ##### Return Types  By default, all data is returned as JSON. Send `?_format=csv` to get CSV data or `?_format=xml` to get XML data.  ##### Trade Data Queries  *This is only a small subset of what is available, to get you started.*  Fill in the parameters and click the `Try it out!` button to try any of these queries.  * [Pricing Data](#!/Quote/Quote_get)  * [Trade Data](#!/Trade/Trade_get)  * [OrderBook Data](#!/OrderBook/OrderBook_getL2)  * [Settlement Data](#!/Settlement/Settlement_get)  * [Exchange Statistics](#!/Stats/Stats_history)  Every function of the BitMEX.com platform is exposed here and documented. Many more functions are available.  ##### Swagger Specification  [⇩ Download Swagger JSON](swagger.json)    ## All API Endpoints  Click to expand a section. 
 *
 * OpenAPI spec version: 1.2.0
 * Contact: support@bitmex.com
 *
 * NOTE: This class is auto generated by the swagger code generator 2.4.0-SNAPSHOT.
 * https://github.com/swagger-api/swagger-codegen.git
 * Do not edit the class manually.
 */

/*
 * APIKey.h
 *
 * Persistent API Keys for Developers
 */

#ifndef IO_SWAGGER_CLIENT_MODEL_APIKey_H_
#define IO_SWAGGER_CLIENT_MODEL_APIKey_H_


#include "../ModelBase.h"

#include "X-any.h"
#include <cpprest/details/basic_types.h>
#include <vector>

namespace io {
namespace swagger {
namespace client {
namespace model {

/// <summary>
/// Persistent API Keys for Developers
/// </summary>
class  APIKey
    : public ModelBase
{
public:
    APIKey();
    virtual ~APIKey();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    void fromJson(web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    void fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// APIKey members

    /// <summary>
    /// 
    /// </summary>
    utility::string_t getId() const;
        void setId(utility::string_t value);
    /// <summary>
    /// 
    /// </summary>
    utility::string_t getSecret() const;
        void setSecret(utility::string_t value);
    /// <summary>
    /// 
    /// </summary>
    utility::string_t getName() const;
        void setName(utility::string_t value);
    /// <summary>
    /// 
    /// </summary>
    double getNonce() const;
        void setNonce(double value);
    /// <summary>
    /// 
    /// </summary>
    utility::string_t getCidr() const;
    bool cidrIsSet() const;
    void unsetCidr();
    void setCidr(utility::string_t value);
    /// <summary>
    /// 
    /// </summary>
    std::vector<std::shared_ptr<Xany>>& getPermissions();
    bool permissionsIsSet() const;
    void unsetPermissions();
    void setPermissions(std::vector<std::shared_ptr<Xany>> value);
    /// <summary>
    /// 
    /// </summary>
    bool isEnabled() const;
    bool enabledIsSet() const;
    void unsetEnabled();
    void setEnabled(bool value);
    /// <summary>
    /// 
    /// </summary>
    double getUserId() const;
        void setUserId(double value);
    /// <summary>
    /// 
    /// </summary>
    utility::datetime getCreated() const;
    bool createdIsSet() const;
    void unsetCreated();
    void setCreated(utility::datetime value);

protected:
    utility::string_t m_Id;
        utility::string_t m_Secret;
        utility::string_t m_Name;
        double m_Nonce;
        utility::string_t m_Cidr;
    bool m_CidrIsSet;
    std::vector<std::shared_ptr<Xany>> m_Permissions;
    bool m_PermissionsIsSet;
    bool m_Enabled;
    bool m_EnabledIsSet;
    double m_UserId;
        utility::datetime m_Created;
    bool m_CreatedIsSet;
};

}
}
}
}

#endif /* IO_SWAGGER_CLIENT_MODEL_APIKey_H_ */
