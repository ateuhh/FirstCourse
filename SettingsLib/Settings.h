#ifndef SETTINGS_H
#define SETTINGS_H

#include <fstream>
#include <iostream> 
#include <map>
#include <string>
#include <vector>

class settings {

    private:
    	void keep();          // this function keeps new settings
    	void VerifyData();    // this function verifys filename 
        std :: string file;
        std :: map <std :: string,string > settings;

    public:
        // Main functions

        /**
         * Construct settings store
         * and load data from file (if exists)
         * \param filename Path to file with settings
         */

        settings(std::string const & filename);
        /**
         * Get setting value
         * \param name Setting unique identifier
         * \param def Default setting value
         * \return Stored value for given name or default value
         */
        std::string const & get(std::string const & name, 
			std::string const & def = "") const;
        /**
         * Set or replace setting value and save changes to file
         * \param name Setting unique identifier
         * \param value New setting value
         */
        void set(std::string const & name,
            std::string const & value);
        /**
         * Reset all settings
         */
        void reset();
        /**
         * Reload all settings from file
         */
        void reload();

        // Advanced funntions
};


#endif // SETTINGS_H
