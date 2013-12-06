#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

namespace configuration{

//namespace load{
//void parameterEstimationSettings(const std::string &filename)
//{
////    // Create empty property tree object
////    using boost::property_tree::ptree;
////    ptree pt;

////    // Load XML file and put its contents in property tree.
////    // No namespace qualification is needed, because of Koenig
////    // lookup on the second argument. If reading fails, exception
////    // is thrown.
////    read_xml(filename, pt);

////    // Get filename and store it in m_file variable. Note that
////    // we specify a path to the value using notation where keys
////    // are separated with dots (different separator may be used
////    // if keys themselves contain dots). If debug.filename key is
////    // not found, exception is thrown.
////    m_file = pt.get<std::string>("debug.filename");

////    // Get debug level and store it in m_level variable. This is
////    // another version of get method: if debug.level key is not
////    // found, it will return default value (specified by second
////    // parameter) instead of throwing. Type of the value extracted
////    // is determined by type of second parameter, so we can simply
////    // write get(...) instead of get<int>(...).
////    m_level = pt.get("debug.level", 0);

////    // Iterate over debug.modules section and store all found
////    // modules in m_modules set. get_child() function returns a
////    // reference to child at specified path; if there is no such
////    // child, it throws. Property tree iterator can be used in
////    // the same way as standard container iterator. Category
////    // is bidirectional_iterator.
////    //BOOST_FOREACH(ptree::value_type &v, pt.get_child("debug.modules"))
////    //    m_modules.insert(v.second.data());
//}
//}

//namespace save{
//void parameterEstimationSettings(const std::string &filename)
//{

////    // Create empty property tree object
////    using boost::property_tree::ptree;
////    ptree pt;

////    // Put log filename in property tree
////    pt.put("debug.filename", m_file);

////    // Put debug level in property tree
////    pt.put("debug.level", m_level);

////    // Iterate over modules in set and put them in property
////    // tree. Note that put function places new key at the
////    // end of list of keys. This is fine in most of the
////    // situations. If you want to place item at some other
////    // place (i.e. at front or somewhere in the middle),
////    // this can be achieved using combination of insert
////    // and put_value functions
////    //BOOST_FOREACH(const std::string &name, m_modules)
////    //    pt.put("debug.modules.module", name, true);

////    // Write property tree to XML file
////    write_xml(filename, pt);
//}
//}


}


#endif // CONFIGURATION_HPP
