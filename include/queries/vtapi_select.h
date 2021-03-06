/**
 * @file
 * @brief   Declaration of Select class
 *
 * @author   Petr Chmelar, chmelarp (at) fit.vutbr.cz
 * @author   Vojtech Froml, xfroml00 (at) stud.fit.vutbr.cz
 * @author   Tomas Volf, ivolf (at) fit.vutbr.cz
 * 
 * @licence   @ref licence "BUT OPEN SOURCE LICENCE (Version 1)"
 * 
 * @copyright   &copy; 2011 &ndash; 2015, Brno University of Technology
 */

#ifndef VTAPI_SELECT_H
#define	VTAPI_SELECT_H


#include "vtapi_query.h"

namespace vtapi {

    
/**
 * @brief Class for constructing and executing SELECT queries
 * 
 * @see Basic information on page @ref KEYVALUES
 * 
 * @note Error codes 21*
 * 
 * @author   Petr Chmelar, chmelarp (at) fit.vutbr.cz
 * @author   Vojtech Froml, xfroml00 (at) stud.fit.vutbr.cz
 * @author   Tomas Volf, ivolf (at) fit.vutbr.cz
 * 
 * @licence   @ref licence "BUT OPEN SOURCE LICENCE (Version 1)"
 * 
 * @copyright   &copy; 2011 &ndash; 2015, Brno University of Technology
 */
class Select : public Query {
protected:

    std::string                     groupby;    /**< String used for the GROUP BY statement */
    std::string                     orderby;    /**< String used for the ORDER BY statement */

    int                             limit;      /**< Specify a size (a number of rows) of the resultset */
    int                             offset;     /**< Specify an index of row, where the resultset starts */

public:

    /**
     * Constructor of a SELECT query object
     * @param commons      configuration object of Commons class
     * @param initString   initialization string (partial or full query)
     */
    Select(const Commons& commons, const std::string& initString = "");
    /**
     * Gets SELECT query string
     * @return query string
     */
    std::string getQuery();
    /**
     * Executes SELECT query and fetches result
     * @return success
     */
    bool execute();
    /**
     * Shifts offset, executes SELECT query and fetches result
     * @return success
     */
    bool executeNext();
    /**
     * This is used to specify a function in the (column) list
     * @note It may be called more times.
     * @unimplemented
     */
    bool function(const std::string& funtext);
    /**
     * This is used to join tables if they can be performed automatically. 
     * If not, returns false (no quarantee before version 2).
     * @warning no quarantee before version 2 !!
     * @return success
     * @unimplemented
     */
    bool join();
    /**
     * Gets number of rows to be fetched by LIMIT section of query
     * @return number of rows specified in LIMIT section
     */
    int getLimit() { return this->limit; };
    /**
     * Sets number of rows to be fetched by LIMIT section of query
     * @param limit   number of rows to be fetched
     */
    void setLimit(const int limit) { this->limit = limit; };
    /**
     * This is used to specify a table for FROM statement and a column list for SELECT statement
     * @param table    table to select
     * @param column   column for select
     * @return success
     * @note It may be called more times.
     */
    bool from(const std::string& table, const std::string& column);
    /**
     * This is a WHERE statement construction function for strings
     * @param key     key to compare with a value
     * @param value   requested value for key
     * @param oper    comparision operator between key and value
     * @param from    table where the key is situated
     * @return success
     * @note It may be called several times.
     */
    bool whereString(const std::string& key, const std::string& value, const std::string& oper = "=", const std::string& from = "");
    /**
     * This is a WHERE statement construction function for integers
     * @param key     key to compare with a value
     * @param value   requested value for key
     * @param oper    comparision operator between key and value
     * @param from    table where the key is situated
     * @return success
     * @note It may be called several times.
     */
    bool whereInt(const std::string& key, const int value, const std::string& oper = "=", const std::string& from = "");
    /**
     * This is a WHERE statement construction function for floats
     * @param key     key to compare with a value
     * @param value   requested value for key
     * @param oper    comparison operator between key and value
     * @param from    table where the key is situated
     * @return success
     * @note It may be called several times.
     */
    bool whereFloat(const std::string& key, const float value, const std::string& oper = "=", const std::string& from = "");
    /**
     * This is a WHERE statement construction function for seqtype
     * @param key     key to compare with a value
     * @param value   requested value for key
     * @param oper    comparison operator between key and value
     * @param from    table where the key is situated
     * @return success
     * @note It may be called several times.
     */
     bool whereSeqtype(const std::string& key, const std::string& value, const std::string& oper = "=", const std::string& from = "");
    /**
     * This is a WHERE statement construction function for inouttype
     * @param key     key to compare with a value
     * @param value   requested value for key
     * @param oper    comparison operator between key and value
     * @param from    table where the key is situated
     * @return success
     * @note It may be called several times.
     */
     bool whereInouttype(const std::string& key, const std::string& value, const std::string& oper = "=", const std::string& from = "");
    /**
     * This is a WHERE statement construction function for pstate type
     * @param key     key to compare with a value
     * @param value   requested value for key
     * @param oper    comparison operator between key and value
     * @param from    table where the key is situated
     * @return success
     * @note It may be called several times.
     */
     bool wherePStatus(const std::string& key, ProcessState::STATUS_T value, const std::string& oper = "=", const std::string& from = "");
    /**
     * This is a WHERE statement construction function for timestamp
     * @param key     key to compare with a value
     * @param value   requested value for key
     * @param oper    comparison operator between key and value
     * @param from    table where the key is situated
     * @return success
     * @note It may be called several times.
     */
     bool whereTimestamp(const std::string& key, const time_t& value, const std::string& oper = "=", const std::string& from = "");
     /**
      * This is a WHERE statement construction function for filters by overlapping time ranges
      * @param key_start    key with range start time [timestamp]
      * @param key_length   key with range length [s]
      * @param value_start  compared range start time [UNIX time]
      * @param value_length compared range length [s]
      * @param oper comparison operator between ranges
      * @param from table where keys are situated
      * @return success
      */
     bool whereTimeRange(const std::string& key_start, const std::string& key_length, const time_t& value_start, const uint value_length, const std::string& oper = "&&", const std::string& from = "");
     /**
     * This is a WHERE statement construction function for filters by geometric box region
     * @param key  key to compare with a value
     * @param value requested value for key
     * @param oper comparison operator between key and value
     * @param from    table where the key is situated
     * @return success
     */
     bool whereRegion(const std::string& key, const IntervalEvent::box& value, const std::string& oper = "&&", const std::string& from = "");
    /**
     * This is a WHERE statement construction function for custom expression
     * @param expression expression
     * @param value requested value for expression
     * @param oper comparison operator between expression and value
     * @return  success
     */
     bool whereExpression(const std::string& expression, const std::string& value, const std::string& oper = "=");

};

} // namespace vtapi

#endif	/* VTAPI_SELECT_H */

