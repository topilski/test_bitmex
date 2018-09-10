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



#include "Order.h"

namespace io {
namespace swagger {
namespace client {
namespace model {

Order::Order()
{
    m_OrderID = utility::conversions::to_string_t("");
    m_ClOrdID = utility::conversions::to_string_t("");
    m_ClOrdIDIsSet = false;
    m_ClOrdLinkID = utility::conversions::to_string_t("");
    m_ClOrdLinkIDIsSet = false;
    m_Account = 0.0;
    m_AccountIsSet = false;
    m_Symbol = utility::conversions::to_string_t("");
    m_SymbolIsSet = false;
    m_Side = utility::conversions::to_string_t("");
    m_SideIsSet = false;
    m_SimpleOrderQty = 0.0;
    m_SimpleOrderQtyIsSet = false;
    m_OrderQty = 0.0;
    m_OrderQtyIsSet = false;
    m_Price = 0.0;
    m_PriceIsSet = false;
    m_DisplayQty = 0.0;
    m_DisplayQtyIsSet = false;
    m_StopPx = 0.0;
    m_StopPxIsSet = false;
    m_PegOffsetValue = 0.0;
    m_PegOffsetValueIsSet = false;
    m_PegPriceType = utility::conversions::to_string_t("");
    m_PegPriceTypeIsSet = false;
    m_Currency = utility::conversions::to_string_t("");
    m_CurrencyIsSet = false;
    m_SettlCurrency = utility::conversions::to_string_t("");
    m_SettlCurrencyIsSet = false;
    m_OrdType = utility::conversions::to_string_t("");
    m_OrdTypeIsSet = false;
    m_TimeInForce = utility::conversions::to_string_t("");
    m_TimeInForceIsSet = false;
    m_ExecInst = utility::conversions::to_string_t("");
    m_ExecInstIsSet = false;
    m_ContingencyType = utility::conversions::to_string_t("");
    m_ContingencyTypeIsSet = false;
    m_ExDestination = utility::conversions::to_string_t("");
    m_ExDestinationIsSet = false;
    m_OrdStatus = utility::conversions::to_string_t("");
    m_OrdStatusIsSet = false;
    m_Triggered = utility::conversions::to_string_t("");
    m_TriggeredIsSet = false;
    m_WorkingIndicator = false;
    m_WorkingIndicatorIsSet = false;
    m_OrdRejReason = utility::conversions::to_string_t("");
    m_OrdRejReasonIsSet = false;
    m_SimpleLeavesQty = 0.0;
    m_SimpleLeavesQtyIsSet = false;
    m_LeavesQty = 0.0;
    m_LeavesQtyIsSet = false;
    m_SimpleCumQty = 0.0;
    m_SimpleCumQtyIsSet = false;
    m_CumQty = 0.0;
    m_CumQtyIsSet = false;
    m_AvgPx = 0.0;
    m_AvgPxIsSet = false;
    m_MultiLegReportingType = utility::conversions::to_string_t("");
    m_MultiLegReportingTypeIsSet = false;
    m_Text = utility::conversions::to_string_t("");
    m_TextIsSet = false;
    m_TransactTime = utility::datetime();
    m_TransactTimeIsSet = false;
    m_Timestamp = utility::datetime();
    m_TimestampIsSet = false;
}

Order::~Order()
{
}

void Order::validate()
{
    // TODO: implement validation
}

web::json::value Order::toJson() const
{
    web::json::value val = web::json::value::object();

    val[utility::conversions::to_string_t("orderID")] = ModelBase::toJson(m_OrderID);
    if(m_ClOrdIDIsSet)
    {
        val[utility::conversions::to_string_t("clOrdID")] = ModelBase::toJson(m_ClOrdID);
    }
    if(m_ClOrdLinkIDIsSet)
    {
        val[utility::conversions::to_string_t("clOrdLinkID")] = ModelBase::toJson(m_ClOrdLinkID);
    }
    if(m_AccountIsSet)
    {
        val[utility::conversions::to_string_t("account")] = ModelBase::toJson(m_Account);
    }
    if(m_SymbolIsSet)
    {
        val[utility::conversions::to_string_t("symbol")] = ModelBase::toJson(m_Symbol);
    }
    if(m_SideIsSet)
    {
        val[utility::conversions::to_string_t("side")] = ModelBase::toJson(m_Side);
    }
    if(m_SimpleOrderQtyIsSet)
    {
        val[utility::conversions::to_string_t("simpleOrderQty")] = ModelBase::toJson(m_SimpleOrderQty);
    }
    if(m_OrderQtyIsSet)
    {
        val[utility::conversions::to_string_t("orderQty")] = ModelBase::toJson(m_OrderQty);
    }
    if(m_PriceIsSet)
    {
        val[utility::conversions::to_string_t("price")] = ModelBase::toJson(m_Price);
    }
    if(m_DisplayQtyIsSet)
    {
        val[utility::conversions::to_string_t("displayQty")] = ModelBase::toJson(m_DisplayQty);
    }
    if(m_StopPxIsSet)
    {
        val[utility::conversions::to_string_t("stopPx")] = ModelBase::toJson(m_StopPx);
    }
    if(m_PegOffsetValueIsSet)
    {
        val[utility::conversions::to_string_t("pegOffsetValue")] = ModelBase::toJson(m_PegOffsetValue);
    }
    if(m_PegPriceTypeIsSet)
    {
        val[utility::conversions::to_string_t("pegPriceType")] = ModelBase::toJson(m_PegPriceType);
    }
    if(m_CurrencyIsSet)
    {
        val[utility::conversions::to_string_t("currency")] = ModelBase::toJson(m_Currency);
    }
    if(m_SettlCurrencyIsSet)
    {
        val[utility::conversions::to_string_t("settlCurrency")] = ModelBase::toJson(m_SettlCurrency);
    }
    if(m_OrdTypeIsSet)
    {
        val[utility::conversions::to_string_t("ordType")] = ModelBase::toJson(m_OrdType);
    }
    if(m_TimeInForceIsSet)
    {
        val[utility::conversions::to_string_t("timeInForce")] = ModelBase::toJson(m_TimeInForce);
    }
    if(m_ExecInstIsSet)
    {
        val[utility::conversions::to_string_t("execInst")] = ModelBase::toJson(m_ExecInst);
    }
    if(m_ContingencyTypeIsSet)
    {
        val[utility::conversions::to_string_t("contingencyType")] = ModelBase::toJson(m_ContingencyType);
    }
    if(m_ExDestinationIsSet)
    {
        val[utility::conversions::to_string_t("exDestination")] = ModelBase::toJson(m_ExDestination);
    }
    if(m_OrdStatusIsSet)
    {
        val[utility::conversions::to_string_t("ordStatus")] = ModelBase::toJson(m_OrdStatus);
    }
    if(m_TriggeredIsSet)
    {
        val[utility::conversions::to_string_t("triggered")] = ModelBase::toJson(m_Triggered);
    }
    if(m_WorkingIndicatorIsSet)
    {
        val[utility::conversions::to_string_t("workingIndicator")] = ModelBase::toJson(m_WorkingIndicator);
    }
    if(m_OrdRejReasonIsSet)
    {
        val[utility::conversions::to_string_t("ordRejReason")] = ModelBase::toJson(m_OrdRejReason);
    }
    if(m_SimpleLeavesQtyIsSet)
    {
        val[utility::conversions::to_string_t("simpleLeavesQty")] = ModelBase::toJson(m_SimpleLeavesQty);
    }
    if(m_LeavesQtyIsSet)
    {
        val[utility::conversions::to_string_t("leavesQty")] = ModelBase::toJson(m_LeavesQty);
    }
    if(m_SimpleCumQtyIsSet)
    {
        val[utility::conversions::to_string_t("simpleCumQty")] = ModelBase::toJson(m_SimpleCumQty);
    }
    if(m_CumQtyIsSet)
    {
        val[utility::conversions::to_string_t("cumQty")] = ModelBase::toJson(m_CumQty);
    }
    if(m_AvgPxIsSet)
    {
        val[utility::conversions::to_string_t("avgPx")] = ModelBase::toJson(m_AvgPx);
    }
    if(m_MultiLegReportingTypeIsSet)
    {
        val[utility::conversions::to_string_t("multiLegReportingType")] = ModelBase::toJson(m_MultiLegReportingType);
    }
    if(m_TextIsSet)
    {
        val[utility::conversions::to_string_t("text")] = ModelBase::toJson(m_Text);
    }
    if(m_TransactTimeIsSet)
    {
        val[utility::conversions::to_string_t("transactTime")] = ModelBase::toJson(m_TransactTime);
    }
    if(m_TimestampIsSet)
    {
        val[utility::conversions::to_string_t("timestamp")] = ModelBase::toJson(m_Timestamp);
    }

    return val;
}

void Order::fromJson(web::json::value& val)
{
    setOrderID(ModelBase::stringFromJson(val[utility::conversions::to_string_t("orderID")]));
    if(val.has_field(utility::conversions::to_string_t("clOrdID")))
    {
        setClOrdID(ModelBase::stringFromJson(val[utility::conversions::to_string_t("clOrdID")]));
    }
    if(val.has_field(utility::conversions::to_string_t("clOrdLinkID")))
    {
        setClOrdLinkID(ModelBase::stringFromJson(val[utility::conversions::to_string_t("clOrdLinkID")]));
    }
    if(val.has_field(utility::conversions::to_string_t("account")))
    {
        setAccount(ModelBase::doubleFromJson(val[utility::conversions::to_string_t("account")]));
    }
    if(val.has_field(utility::conversions::to_string_t("symbol")))
    {
        setSymbol(ModelBase::stringFromJson(val[utility::conversions::to_string_t("symbol")]));
    }
    if(val.has_field(utility::conversions::to_string_t("side")))
    {
        setSide(ModelBase::stringFromJson(val[utility::conversions::to_string_t("side")]));
    }
    if(val.has_field(utility::conversions::to_string_t("simpleOrderQty")))
    {
        //setSimpleOrderQty(ModelBase::doubleFromJson(val[utility::conversions::to_string_t("simpleOrderQty")]));
    }
    if(val.has_field(utility::conversions::to_string_t("orderQty")))
    {
        setOrderQty(ModelBase::doubleFromJson(val[utility::conversions::to_string_t("orderQty")]));
    }
    if(val.has_field(utility::conversions::to_string_t("price")))
    {
        setPrice(ModelBase::doubleFromJson(val[utility::conversions::to_string_t("price")]));
    }
    if(val.has_field(utility::conversions::to_string_t("displayQty")))
    {
        //setDisplayQty(ModelBase::doubleFromJson(val[utility::conversions::to_string_t("displayQty")]));
    }
    if(val.has_field(utility::conversions::to_string_t("stopPx")))
    {
        //setStopPx(ModelBase::doubleFromJson(val[utility::conversions::to_string_t("stopPx")]));
    }
    if(val.has_field(utility::conversions::to_string_t("pegOffsetValue")))
    {
        // setPegOffsetValue(ModelBase::doubleFromJson(val[utility::conversions::to_string_t("pegOffsetValue")]));
    }
    if(val.has_field(utility::conversions::to_string_t("pegPriceType")))
    {
        setPegPriceType(ModelBase::stringFromJson(val[utility::conversions::to_string_t("pegPriceType")]));
    }
    if(val.has_field(utility::conversions::to_string_t("currency")))
    {
        setCurrency(ModelBase::stringFromJson(val[utility::conversions::to_string_t("currency")]));
    }
    if(val.has_field(utility::conversions::to_string_t("settlCurrency")))
    {
        setSettlCurrency(ModelBase::stringFromJson(val[utility::conversions::to_string_t("settlCurrency")]));
    }
    if(val.has_field(utility::conversions::to_string_t("ordType")))
    {
        setOrdType(ModelBase::stringFromJson(val[utility::conversions::to_string_t("ordType")]));
    }
    if(val.has_field(utility::conversions::to_string_t("timeInForce")))
    {
        setTimeInForce(ModelBase::stringFromJson(val[utility::conversions::to_string_t("timeInForce")]));
    }
    if(val.has_field(utility::conversions::to_string_t("execInst")))
    {
        setExecInst(ModelBase::stringFromJson(val[utility::conversions::to_string_t("execInst")]));
    }
    if(val.has_field(utility::conversions::to_string_t("contingencyType")))
    {
        setContingencyType(ModelBase::stringFromJson(val[utility::conversions::to_string_t("contingencyType")]));
    }
    if(val.has_field(utility::conversions::to_string_t("exDestination")))
    {
        setExDestination(ModelBase::stringFromJson(val[utility::conversions::to_string_t("exDestination")]));
    }
    if(val.has_field(utility::conversions::to_string_t("ordStatus")))
    {
        setOrdStatus(ModelBase::stringFromJson(val[utility::conversions::to_string_t("ordStatus")]));
    }
    if(val.has_field(utility::conversions::to_string_t("triggered")))
    {
        setTriggered(ModelBase::stringFromJson(val[utility::conversions::to_string_t("triggered")]));
    }
    if(val.has_field(utility::conversions::to_string_t("workingIndicator")))
    {
        setWorkingIndicator(ModelBase::boolFromJson(val[utility::conversions::to_string_t("workingIndicator")]));
    }
    if(val.has_field(utility::conversions::to_string_t("ordRejReason")))
    {
        setOrdRejReason(ModelBase::stringFromJson(val[utility::conversions::to_string_t("ordRejReason")]));
    }
    if(val.has_field(utility::conversions::to_string_t("simpleLeavesQty")))
    {
        setSimpleLeavesQty(ModelBase::doubleFromJson(val[utility::conversions::to_string_t("simpleLeavesQty")]));
    }
    if(val.has_field(utility::conversions::to_string_t("leavesQty")))
    {
        setLeavesQty(ModelBase::doubleFromJson(val[utility::conversions::to_string_t("leavesQty")]));
    }
    if(val.has_field(utility::conversions::to_string_t("simpleCumQty")))
    {
        setSimpleCumQty(ModelBase::doubleFromJson(val[utility::conversions::to_string_t("simpleCumQty")]));
    }
    if(val.has_field(utility::conversions::to_string_t("cumQty")))
    {
        setCumQty(ModelBase::doubleFromJson(val[utility::conversions::to_string_t("cumQty")]));
    }
    if(val.has_field(utility::conversions::to_string_t("avgPx")))
    {
        setAvgPx(ModelBase::doubleFromJson(val[utility::conversions::to_string_t("avgPx")]));
    }
    if(val.has_field(utility::conversions::to_string_t("multiLegReportingType")))
    {
        setMultiLegReportingType(ModelBase::stringFromJson(val[utility::conversions::to_string_t("multiLegReportingType")]));
    }
    if(val.has_field(utility::conversions::to_string_t("text")))
    {
        setText(ModelBase::stringFromJson(val[utility::conversions::to_string_t("text")]));
    }
    if(val.has_field(utility::conversions::to_string_t("transactTime")))
    {
        setTransactTime(ModelBase::dateFromJson(val[utility::conversions::to_string_t("transactTime")]));
    }
    if(val.has_field(utility::conversions::to_string_t("timestamp")))
    {
        setTimestamp(ModelBase::dateFromJson(val[utility::conversions::to_string_t("timestamp")]));
    }
}

void Order::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t("."))
    {
        namePrefix += utility::conversions::to_string_t(".");
    }

    multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("orderID"), m_OrderID));
    if(m_ClOrdIDIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("clOrdID"), m_ClOrdID));
        
    }
    if(m_ClOrdLinkIDIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("clOrdLinkID"), m_ClOrdLinkID));
        
    }
    if(m_AccountIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("account"), m_Account));
    }
    if(m_SymbolIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("symbol"), m_Symbol));
        
    }
    if(m_SideIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("side"), m_Side));
        
    }
    if(m_SimpleOrderQtyIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("simpleOrderQty"), m_SimpleOrderQty));
    }
    if(m_OrderQtyIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("orderQty"), m_OrderQty));
    }
    if(m_PriceIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("price"), m_Price));
    }
    if(m_DisplayQtyIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("displayQty"), m_DisplayQty));
    }
    if(m_StopPxIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("stopPx"), m_StopPx));
    }
    if(m_PegOffsetValueIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("pegOffsetValue"), m_PegOffsetValue));
    }
    if(m_PegPriceTypeIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("pegPriceType"), m_PegPriceType));
        
    }
    if(m_CurrencyIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("currency"), m_Currency));
        
    }
    if(m_SettlCurrencyIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("settlCurrency"), m_SettlCurrency));
        
    }
    if(m_OrdTypeIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("ordType"), m_OrdType));
        
    }
    if(m_TimeInForceIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("timeInForce"), m_TimeInForce));
        
    }
    if(m_ExecInstIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("execInst"), m_ExecInst));
        
    }
    if(m_ContingencyTypeIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("contingencyType"), m_ContingencyType));
        
    }
    if(m_ExDestinationIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("exDestination"), m_ExDestination));
        
    }
    if(m_OrdStatusIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("ordStatus"), m_OrdStatus));
        
    }
    if(m_TriggeredIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("triggered"), m_Triggered));
        
    }
    if(m_WorkingIndicatorIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("workingIndicator"), m_WorkingIndicator));
    }
    if(m_OrdRejReasonIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("ordRejReason"), m_OrdRejReason));
        
    }
    if(m_SimpleLeavesQtyIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("simpleLeavesQty"), m_SimpleLeavesQty));
    }
    if(m_LeavesQtyIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("leavesQty"), m_LeavesQty));
    }
    if(m_SimpleCumQtyIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("simpleCumQty"), m_SimpleCumQty));
    }
    if(m_CumQtyIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("cumQty"), m_CumQty));
    }
    if(m_AvgPxIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("avgPx"), m_AvgPx));
    }
    if(m_MultiLegReportingTypeIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("multiLegReportingType"), m_MultiLegReportingType));
        
    }
    if(m_TextIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("text"), m_Text));
        
    }
    if(m_TransactTimeIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("transactTime"), m_TransactTime));
        
    }
    if(m_TimestampIsSet)
    {
        multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("timestamp"), m_Timestamp));
        
    }
}

void Order::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t("."))
    {
        namePrefix += utility::conversions::to_string_t(".");
    }

    setOrderID(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("orderID"))));
    if(multipart->hasContent(utility::conversions::to_string_t("clOrdID")))
    {
        setClOrdID(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("clOrdID"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("clOrdLinkID")))
    {
        setClOrdLinkID(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("clOrdLinkID"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("account")))
    {
        setAccount(ModelBase::doubleFromHttpContent(multipart->getContent(utility::conversions::to_string_t("account"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("symbol")))
    {
        setSymbol(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("symbol"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("side")))
    {
        setSide(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("side"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("simpleOrderQty")))
    {
        setSimpleOrderQty(ModelBase::doubleFromHttpContent(multipart->getContent(utility::conversions::to_string_t("simpleOrderQty"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("orderQty")))
    {
        setOrderQty(ModelBase::doubleFromHttpContent(multipart->getContent(utility::conversions::to_string_t("orderQty"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("price")))
    {
        setPrice(ModelBase::doubleFromHttpContent(multipart->getContent(utility::conversions::to_string_t("price"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("displayQty")))
    {
        setDisplayQty(ModelBase::doubleFromHttpContent(multipart->getContent(utility::conversions::to_string_t("displayQty"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("stopPx")))
    {
        setStopPx(ModelBase::doubleFromHttpContent(multipart->getContent(utility::conversions::to_string_t("stopPx"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("pegOffsetValue")))
    {
        setPegOffsetValue(ModelBase::doubleFromHttpContent(multipart->getContent(utility::conversions::to_string_t("pegOffsetValue"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("pegPriceType")))
    {
        setPegPriceType(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("pegPriceType"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("currency")))
    {
        setCurrency(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("currency"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("settlCurrency")))
    {
        setSettlCurrency(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("settlCurrency"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("ordType")))
    {
        setOrdType(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("ordType"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("timeInForce")))
    {
        setTimeInForce(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("timeInForce"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("execInst")))
    {
        setExecInst(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("execInst"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("contingencyType")))
    {
        setContingencyType(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("contingencyType"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("exDestination")))
    {
        setExDestination(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("exDestination"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("ordStatus")))
    {
        setOrdStatus(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("ordStatus"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("triggered")))
    {
        setTriggered(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("triggered"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("workingIndicator")))
    {
        setWorkingIndicator(ModelBase::boolFromHttpContent(multipart->getContent(utility::conversions::to_string_t("workingIndicator"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("ordRejReason")))
    {
        setOrdRejReason(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("ordRejReason"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("simpleLeavesQty")))
    {
        setSimpleLeavesQty(ModelBase::doubleFromHttpContent(multipart->getContent(utility::conversions::to_string_t("simpleLeavesQty"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("leavesQty")))
    {
        setLeavesQty(ModelBase::doubleFromHttpContent(multipart->getContent(utility::conversions::to_string_t("leavesQty"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("simpleCumQty")))
    {
        setSimpleCumQty(ModelBase::doubleFromHttpContent(multipart->getContent(utility::conversions::to_string_t("simpleCumQty"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("cumQty")))
    {
        setCumQty(ModelBase::doubleFromHttpContent(multipart->getContent(utility::conversions::to_string_t("cumQty"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("avgPx")))
    {
        setAvgPx(ModelBase::doubleFromHttpContent(multipart->getContent(utility::conversions::to_string_t("avgPx"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("multiLegReportingType")))
    {
        setMultiLegReportingType(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("multiLegReportingType"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("text")))
    {
        setText(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("text"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("transactTime")))
    {
        setTransactTime(ModelBase::dateFromHttpContent(multipart->getContent(utility::conversions::to_string_t("transactTime"))));
    }
    if(multipart->hasContent(utility::conversions::to_string_t("timestamp")))
    {
        setTimestamp(ModelBase::dateFromHttpContent(multipart->getContent(utility::conversions::to_string_t("timestamp"))));
    }
}

utility::string_t Order::getOrderID() const
{
    return m_OrderID;
}


void Order::setOrderID(utility::string_t value)
{
    m_OrderID = value;
    
}
utility::string_t Order::getClOrdID() const
{
    return m_ClOrdID;
}


void Order::setClOrdID(utility::string_t value)
{
    m_ClOrdID = value;
    m_ClOrdIDIsSet = true;
}
bool Order::clOrdIDIsSet() const
{
    return m_ClOrdIDIsSet;
}

void Order::unsetClOrdID()
{
    m_ClOrdIDIsSet = false;
}

utility::string_t Order::getClOrdLinkID() const
{
    return m_ClOrdLinkID;
}


void Order::setClOrdLinkID(utility::string_t value)
{
    m_ClOrdLinkID = value;
    m_ClOrdLinkIDIsSet = true;
}
bool Order::clOrdLinkIDIsSet() const
{
    return m_ClOrdLinkIDIsSet;
}

void Order::unsetClOrdLinkID()
{
    m_ClOrdLinkIDIsSet = false;
}

double Order::getAccount() const
{
    return m_Account;
}


void Order::setAccount(double value)
{
    m_Account = value;
    m_AccountIsSet = true;
}
bool Order::accountIsSet() const
{
    return m_AccountIsSet;
}

void Order::unsetAccount()
{
    m_AccountIsSet = false;
}

utility::string_t Order::getSymbol() const
{
    return m_Symbol;
}


void Order::setSymbol(utility::string_t value)
{
    m_Symbol = value;
    m_SymbolIsSet = true;
}
bool Order::symbolIsSet() const
{
    return m_SymbolIsSet;
}

void Order::unsetSymbol()
{
    m_SymbolIsSet = false;
}

utility::string_t Order::getSide() const
{
    return m_Side;
}


void Order::setSide(utility::string_t value)
{
    m_Side = value;
    m_SideIsSet = true;
}
bool Order::sideIsSet() const
{
    return m_SideIsSet;
}

void Order::unsetSide()
{
    m_SideIsSet = false;
}

double Order::getSimpleOrderQty() const
{
    return m_SimpleOrderQty;
}


void Order::setSimpleOrderQty(double value)
{
    m_SimpleOrderQty = value;
    m_SimpleOrderQtyIsSet = true;
}
bool Order::simpleOrderQtyIsSet() const
{
    return m_SimpleOrderQtyIsSet;
}

void Order::unsetSimpleOrderQty()
{
    m_SimpleOrderQtyIsSet = false;
}

double Order::getOrderQty() const
{
    return m_OrderQty;
}


void Order::setOrderQty(double value)
{
    m_OrderQty = value;
    m_OrderQtyIsSet = true;
}
bool Order::orderQtyIsSet() const
{
    return m_OrderQtyIsSet;
}

void Order::unsetOrderQty()
{
    m_OrderQtyIsSet = false;
}

double Order::getPrice() const
{
    return m_Price;
}


void Order::setPrice(double value)
{
    m_Price = value;
    m_PriceIsSet = true;
}
bool Order::priceIsSet() const
{
    return m_PriceIsSet;
}

void Order::unsetPrice()
{
    m_PriceIsSet = false;
}

double Order::getDisplayQty() const
{
    return m_DisplayQty;
}


void Order::setDisplayQty(double value)
{
    m_DisplayQty = value;
    m_DisplayQtyIsSet = true;
}
bool Order::displayQtyIsSet() const
{
    return m_DisplayQtyIsSet;
}

void Order::unsetDisplayQty()
{
    m_DisplayQtyIsSet = false;
}

double Order::getStopPx() const
{
    return m_StopPx;
}


void Order::setStopPx(double value)
{
    m_StopPx = value;
    m_StopPxIsSet = true;
}
bool Order::stopPxIsSet() const
{
    return m_StopPxIsSet;
}

void Order::unsetStopPx()
{
    m_StopPxIsSet = false;
}

double Order::getPegOffsetValue() const
{
    return m_PegOffsetValue;
}


void Order::setPegOffsetValue(double value)
{
    m_PegOffsetValue = value;
    m_PegOffsetValueIsSet = true;
}
bool Order::pegOffsetValueIsSet() const
{
    return m_PegOffsetValueIsSet;
}

void Order::unsetPegOffsetValue()
{
    m_PegOffsetValueIsSet = false;
}

utility::string_t Order::getPegPriceType() const
{
    return m_PegPriceType;
}


void Order::setPegPriceType(utility::string_t value)
{
    m_PegPriceType = value;
    m_PegPriceTypeIsSet = true;
}
bool Order::pegPriceTypeIsSet() const
{
    return m_PegPriceTypeIsSet;
}

void Order::unsetPegPriceType()
{
    m_PegPriceTypeIsSet = false;
}

utility::string_t Order::getCurrency() const
{
    return m_Currency;
}


void Order::setCurrency(utility::string_t value)
{
    m_Currency = value;
    m_CurrencyIsSet = true;
}
bool Order::currencyIsSet() const
{
    return m_CurrencyIsSet;
}

void Order::unsetCurrency()
{
    m_CurrencyIsSet = false;
}

utility::string_t Order::getSettlCurrency() const
{
    return m_SettlCurrency;
}


void Order::setSettlCurrency(utility::string_t value)
{
    m_SettlCurrency = value;
    m_SettlCurrencyIsSet = true;
}
bool Order::settlCurrencyIsSet() const
{
    return m_SettlCurrencyIsSet;
}

void Order::unsetSettlCurrency()
{
    m_SettlCurrencyIsSet = false;
}

utility::string_t Order::getOrdType() const
{
    return m_OrdType;
}


void Order::setOrdType(utility::string_t value)
{
    m_OrdType = value;
    m_OrdTypeIsSet = true;
}
bool Order::ordTypeIsSet() const
{
    return m_OrdTypeIsSet;
}

void Order::unsetOrdType()
{
    m_OrdTypeIsSet = false;
}

utility::string_t Order::getTimeInForce() const
{
    return m_TimeInForce;
}


void Order::setTimeInForce(utility::string_t value)
{
    m_TimeInForce = value;
    m_TimeInForceIsSet = true;
}
bool Order::timeInForceIsSet() const
{
    return m_TimeInForceIsSet;
}

void Order::unsetTimeInForce()
{
    m_TimeInForceIsSet = false;
}

utility::string_t Order::getExecInst() const
{
    return m_ExecInst;
}


void Order::setExecInst(utility::string_t value)
{
    m_ExecInst = value;
    m_ExecInstIsSet = true;
}
bool Order::execInstIsSet() const
{
    return m_ExecInstIsSet;
}

void Order::unsetExecInst()
{
    m_ExecInstIsSet = false;
}

utility::string_t Order::getContingencyType() const
{
    return m_ContingencyType;
}


void Order::setContingencyType(utility::string_t value)
{
    m_ContingencyType = value;
    m_ContingencyTypeIsSet = true;
}
bool Order::contingencyTypeIsSet() const
{
    return m_ContingencyTypeIsSet;
}

void Order::unsetContingencyType()
{
    m_ContingencyTypeIsSet = false;
}

utility::string_t Order::getExDestination() const
{
    return m_ExDestination;
}


void Order::setExDestination(utility::string_t value)
{
    m_ExDestination = value;
    m_ExDestinationIsSet = true;
}
bool Order::exDestinationIsSet() const
{
    return m_ExDestinationIsSet;
}

void Order::unsetExDestination()
{
    m_ExDestinationIsSet = false;
}

utility::string_t Order::getOrdStatus() const
{
    return m_OrdStatus;
}


void Order::setOrdStatus(utility::string_t value)
{
    m_OrdStatus = value;
    m_OrdStatusIsSet = true;
}
bool Order::ordStatusIsSet() const
{
    return m_OrdStatusIsSet;
}

void Order::unsetOrdStatus()
{
    m_OrdStatusIsSet = false;
}

utility::string_t Order::getTriggered() const
{
    return m_Triggered;
}


void Order::setTriggered(utility::string_t value)
{
    m_Triggered = value;
    m_TriggeredIsSet = true;
}
bool Order::triggeredIsSet() const
{
    return m_TriggeredIsSet;
}

void Order::unsetTriggered()
{
    m_TriggeredIsSet = false;
}

bool Order::isWorkingIndicator() const
{
    return m_WorkingIndicator;
}


void Order::setWorkingIndicator(bool value)
{
    m_WorkingIndicator = value;
    m_WorkingIndicatorIsSet = true;
}
bool Order::workingIndicatorIsSet() const
{
    return m_WorkingIndicatorIsSet;
}

void Order::unsetWorkingIndicator()
{
    m_WorkingIndicatorIsSet = false;
}

utility::string_t Order::getOrdRejReason() const
{
    return m_OrdRejReason;
}


void Order::setOrdRejReason(utility::string_t value)
{
    m_OrdRejReason = value;
    m_OrdRejReasonIsSet = true;
}
bool Order::ordRejReasonIsSet() const
{
    return m_OrdRejReasonIsSet;
}

void Order::unsetOrdRejReason()
{
    m_OrdRejReasonIsSet = false;
}

double Order::getSimpleLeavesQty() const
{
    return m_SimpleLeavesQty;
}


void Order::setSimpleLeavesQty(double value)
{
    m_SimpleLeavesQty = value;
    m_SimpleLeavesQtyIsSet = true;
}
bool Order::simpleLeavesQtyIsSet() const
{
    return m_SimpleLeavesQtyIsSet;
}

void Order::unsetSimpleLeavesQty()
{
    m_SimpleLeavesQtyIsSet = false;
}

double Order::getLeavesQty() const
{
    return m_LeavesQty;
}


void Order::setLeavesQty(double value)
{
    m_LeavesQty = value;
    m_LeavesQtyIsSet = true;
}
bool Order::leavesQtyIsSet() const
{
    return m_LeavesQtyIsSet;
}

void Order::unsetLeavesQty()
{
    m_LeavesQtyIsSet = false;
}

double Order::getSimpleCumQty() const
{
    return m_SimpleCumQty;
}


void Order::setSimpleCumQty(double value)
{
    m_SimpleCumQty = value;
    m_SimpleCumQtyIsSet = true;
}
bool Order::simpleCumQtyIsSet() const
{
    return m_SimpleCumQtyIsSet;
}

void Order::unsetSimpleCumQty()
{
    m_SimpleCumQtyIsSet = false;
}

double Order::getCumQty() const
{
    return m_CumQty;
}


void Order::setCumQty(double value)
{
    m_CumQty = value;
    m_CumQtyIsSet = true;
}
bool Order::cumQtyIsSet() const
{
    return m_CumQtyIsSet;
}

void Order::unsetCumQty()
{
    m_CumQtyIsSet = false;
}

double Order::getAvgPx() const
{
    return m_AvgPx;
}


void Order::setAvgPx(double value)
{
    m_AvgPx = value;
    m_AvgPxIsSet = true;
}
bool Order::avgPxIsSet() const
{
    return m_AvgPxIsSet;
}

void Order::unsetAvgPx()
{
    m_AvgPxIsSet = false;
}

utility::string_t Order::getMultiLegReportingType() const
{
    return m_MultiLegReportingType;
}


void Order::setMultiLegReportingType(utility::string_t value)
{
    m_MultiLegReportingType = value;
    m_MultiLegReportingTypeIsSet = true;
}
bool Order::multiLegReportingTypeIsSet() const
{
    return m_MultiLegReportingTypeIsSet;
}

void Order::unsetMultiLegReportingType()
{
    m_MultiLegReportingTypeIsSet = false;
}

utility::string_t Order::getText() const
{
    return m_Text;
}


void Order::setText(utility::string_t value)
{
    m_Text = value;
    m_TextIsSet = true;
}
bool Order::textIsSet() const
{
    return m_TextIsSet;
}

void Order::unsetText()
{
    m_TextIsSet = false;
}

utility::datetime Order::getTransactTime() const
{
    return m_TransactTime;
}


void Order::setTransactTime(utility::datetime value)
{
    m_TransactTime = value;
    m_TransactTimeIsSet = true;
}
bool Order::transactTimeIsSet() const
{
    return m_TransactTimeIsSet;
}

void Order::unsetTransactTime()
{
    m_TransactTimeIsSet = false;
}

utility::datetime Order::getTimestamp() const
{
    return m_Timestamp;
}


void Order::setTimestamp(utility::datetime value)
{
    m_Timestamp = value;
    m_TimestampIsSet = true;
}
bool Order::timestampIsSet() const
{
    return m_TimestampIsSet;
}

void Order::unsetTimestamp()
{
    m_TimestampIsSet = false;
}

}
}
}
}

