/**
 * @file
 * @brief   Declaration of Common class and definition of format_t
 *
 * @author   Petr Chmelar, chmelarp (at) fit.vutbr.cz
 * @author   Vojtech Froml, xfroml00 (at) stud.fit.vutbr.cz
 * @author   Tomas Volf, ivolf (at) fit.vutbr.cz
 * 
 * @licence   @ref licence "BUT OPEN SOURCE LICENCE (Version 1)"
 * 
 * @copyright   &copy; 2011 &ndash; 2015, Brno University of Technology
 */

#ifndef VTAPI_COMMONS_H
#define	VTAPI_COMMONS_H

#include "../common/vtapi_config.h"
#include "../common/vtapi_settings.h"
#include "../common/vtapi_logger.h"
#include "../backends/vtapi_connection.h"
#include "../backends/vtapi_backendfactory.h"

namespace vtapi {

/**
 * @brief Output data format
 */
typedef enum {
    STANDARD = 0,   /**< plain text */
    CSV,            /**< comma-separated values format */
    HTML            /**< HTML format */
}  format_t;


/**
 * @brief This is common predecessor to each object in the %VTApi - manages connection, logging and error handling.
 *
 * This class is inherited by many and many other classes, but it manages just single resources,
 * thus there may bee a doom if someone destroys the original ones. Well, destructor should only happen
 * when isDoom is false, which is set by the only constructor: Commons(std::string connStr); .
 *
 * @see Basic information on page @ref KEYVALUES
 *
 * @note Error codes 15*
 * 
 * @author   Petr Chmelar, chmelarp (at) fit.vutbr.cz
 * @author   Vojtech Froml, xfroml00 (at) stud.fit.vutbr.cz
 * @author   Tomas Volf, ivolf (at) fit.vutbr.cz
 * 
 * @licence   @ref licence "BUT OPEN SOURCE LICENCE (Version 1)"
 * 
 * @copyright   &copy; 2011 &ndash; 2015, Brno University of Technology
 *//***************************************************************************/
class Commons {
protected:
    std::string thisClass;   /**< This should be filled in each constructor of a derived class */

    BackendFactory::BACKEND_T backend;  /**< Used backend type */
    BackendBase     *backendBase;       /**< base backend object, will be copied across backend-specific objects */
    Connection      *connection;        /**< Connection object */
    Logger          *logger;            /**< Logger object */

    std::string     configfile;         /**< VTApi config file */
    std::string     dbconn;             /**< Connection string / databases folder */
    format_t        format;             /**< Output format */
    std::string     input;              /**< A filename from which we read an input */
    std::string     output;             /**< A filename into which we write an output */
    std::string     user;               /**< Current user */
    std::string     baseLocation;       /**< Base path location */
    int             queryLimit;         /**< Limit number of rows fetched at once */
    int             arrayLimit;         /**< Limit amount of printed array elements */

    // THESE ARE USED IN THE UNDERLYING CLASSES HIERARCHY FOR ANYTHING NECESSARY
    std::string     dataset;            /**< Current dataset name */
    std::string     datasetLocation;    /**< Current dataset location */
    std::string     sequence;           /**< Current sequence name */
    std::string     sequenceLocation;   /**< Current sequence location */
    std::string     selection;          /**< Current selection name */

    // NOT YET IMPLEMENTED
    std::string     method;             /**< Current method name */
    std::string     process;            /**< Current process name */

    bool            doom;               /**< For destructor purposes */

public:
    /**
     * Full copy constructor from existing Commons class
     * @note The default constructor Commons() should never exist
     * @param orig   previously created Commons class
     */
    Commons(const Commons& orig);
    /**
     * Recommended constructor. All arguments are loaded from gengetopt structure.
     * @note The default constructor Commons() should never exist
     * @param args_info   gengetopt structure of command line/configuration file arguments
     */
    Commons(const gengetopt_args_info& args_info);
    /**
     * Destructor
     */
    ~Commons();
    
    /**
     * @unimplemented
     */
    void read(const std::string& format="");

    // some functions that may be useful
    /**
     * Gets current connector
     * @return connector
     */
    Connection* getConnection();
    /**
     * Gets current logger
     * @return logger
     */
    Logger* getLogger();

    /**
     * Gets name of current dataset
     * @return dataset name
     */
    std::string getDataset();
    /**
     * Gets name of current sequence
     * @return sequence name
     */
    std::string getSequence();
    /**
     * Gets name of current selection
     * @return selection name
     */
    std::string getSelection();
    /**
     * Gets name of current process
     * @return process name
     */
    std::string getProcess();
    /**
     * Gets base location path
     * @return base location
     */
    std::string getBaseLocation();
    /**
     * Gets dataset location path
     * @return dataset location
     */
    std::string getDatasetLocation();
    /**
     * Gets sequence location path
     * @return sequence location
     */
    std::string getSequenceLocation();
    /**
     * Gets data location path
     * @return data location
     */
    std::string getDataLocation();
    /**
     * Gets user name
     * @return user name
     */
    std::string getUser();

    /**
     * Checks commons object for validity (connection etc.)
     * @return success
     */
    bool checkCommonsObject();
    /**
     * This is to check whether a file exists or not
     * @param filepath file path
     * @return success exists
     */
    static bool fileExists(const std::string& filepath);
    /**
     * This is to check whether a directory exists or not
     * @param dirpath directory path
     * @return success exists
     */
    static bool dirExists(const std::string& dirpath);
    
private:

    /**
     * Maps string to format_t
     * @param format   string format
     * @return format_t value
     */
    format_t mapFormat(const std::string& format);

};

} // namespace vtapi

#endif	/* VTAPI_COMMONS_H */

