# CMakeLists.txt for Scarab/library/test
# Author: N. Oblath
# Created: Jan 4, 2016

if( Scarab_ENABLE_TESTING )

    set( lib_dependencies 
        Scarab
    )
    
    set( test_programs
        test_configurator
        test_logger
        test_yaml
    )
    
    
    pbuilder_executables( test_programs lib_dependencies )

endif( Scarab_ENABLE_TESTING )
