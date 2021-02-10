#ifndef __CONFIG_READER_H__
#define __CONFIG_READER_H__
#include <yaml-cpp/yaml.h>


/**
 * @brief Reads the configuration file for the client and gets all the needed data.
 *
 */
class ConfigReader{
 private:
  std::string fileName;
  YAML::Node data;

  /**
   * @brief Reads yaml data.
   *
   */
  YAML::Node getData();

public:
    ConfigReader(std::string fileName);


     /**
     * @brief Reads and returns the screen width.
     *
     */
    int getWidth();

     /**
     * @brief Reads and returns the screen height.
     *
     */
    int getHeight();


    /**
    * @brief Returns true if the window is fullscreen.
    *
    */
    bool fullScreen();
};

#endif
