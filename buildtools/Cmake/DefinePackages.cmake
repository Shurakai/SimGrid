### define source packages

set(EXTRA_DIST
  src/include/mc/datatypes.h
  src/include/mc/mc.h
  src/include/simgrid/platf_interface.h
  src/include/surf/datatypes.h
  src/include/surf/maxmin.h
  src/include/surf/random_mgr.h
  src/include/surf/surf.h
  src/include/surf/surf_resource.h
  src/include/surf/surf_resource_lmm.h
  src/include/surf/surfxml_parse_values.h
  src/include/surf/trace_mgr.h
  src/include/xbt/wine_dbghelp.h
  src/include/xbt/xbt_os_time.h
  src/mk_supernovae.pl
  src/msg/msg_mailbox.h
  src/msg/msg_private.h
  src/portable.h
  src/simdag/dax.dtd
  src/simdag/dax_dtd.c
  src/simdag/dax_dtd.h
  src/simdag/private.h
  src/simix/smx_host_private.h
  src/simix/smx_io_private.h
  src/simix/smx_network_private.h
  src/simix/smx_private.h
  src/simix/smx_process_private.h
  src/simix/smx_smurf_private.h
  src/simix/smx_synchro_private.h
  src/smpi/README
  src/smpi/private.h
  src/smpi/smpi_mpi_dt_private.h
  src/surf/cpu_ti_private.h
  src/surf/platf_generator_private.h
  src/surf/gtnets/gtnets_interface.h
  src/surf/gtnets/gtnets_simulator.h
  src/surf/gtnets/gtnets_topology.h
  src/surf/maxmin_private.h
  src/surf/network_gtnets_private.h
  src/surf/network_ns3_private.h
  src/surf/network_private.h
  src/surf/ns3/my-point-to-point-helper.h
  src/surf/ns3/ns3_interface.h
  src/surf/ns3/ns3_simulator.h
  src/surf/ns3/red-queue.h
  src/surf/simgrid.dtd
  src/surf/simgrid_dtd.c
  src/surf/storage_private.h
  src/surf/surf_private.h
  src/surf/surf_routing_private.h
  src/surf/surfxml_parse.c
  src/surf/trace_mgr_private.h
  src/xbt/automaton/automaton_lexer.yy.c
  src/xbt/automaton/parserPromela.lex
  src/xbt/automaton/parserPromela.tab.cacc
  src/xbt/automaton/parserPromela.tab.hacc
  src/xbt/automaton/parserPromela.yacc
  src/xbt/backtrace_dummy.c
  src/xbt/backtrace_linux.c
  src/xbt/backtrace_windows.c
  src/xbt/dict_private.h
  src/xbt/ex_interface.h
  src/xbt/fifo_private.h
  src/xbt/graph_private.h
  src/xbt/graphxml.c
  src/xbt/graphxml.dtd
  src/xbt/graphxml_parse.c
  src/xbt/heap_private.h
  src/xbt/log_private.h
  src/xbt/mallocator_private.h
  src/xbt/mmalloc/mfree.c
  src/xbt/mmalloc/mm.c
  src/xbt/mmalloc/mm_diff.c
  src/xbt/mmalloc/mm_legacy.c
  src/xbt/mmalloc/mm_module.c
  src/xbt/mmalloc/mmalloc.c
  src/xbt/mmalloc/mmalloc.info
  src/xbt/mmalloc/mmalloc.texi
  src/xbt/mmalloc/mmorecore.c
  src/xbt/mmalloc/mmprivate.h
  src/xbt/mmalloc/mmtrace.awk
  src/xbt/mmalloc/mrealloc.c
  src/xbt/setset_private.h
  src/win32/config.h
  src/xbt/win32_ucontext.c
  include/xbt/win32_ucontext.h
  tools/tesh/run_context.h
  tools/tesh/tesh.h
  )

set(SMPI_SRC
  src/smpi/smpi_base.c
  src/smpi/smpi_bench.c
  src/smpi/smpi_c99.c
  src/smpi/smpi_coll.c
  src/smpi/smpi_comm.c
  src/smpi/smpi_global.c
  src/smpi/smpi_group.c
  src/smpi/smpi_mpi.c
  src/smpi/smpi_mpi_dt.c
  src/smpi/smpi_pmpi.c
  src/smpi/smpi_replay.c
  )
  
if(SMPI_F2C)
  set(SMPI_SRC
    ${SMPI_SRC}
    src/smpi/smpi_f77.c
    )
else()
  set(EXTRA_DIST
    ${EXTRA_DIST}
    src/smpi/smpi_f77.c
  )
endif()


set(XBT_SRC
  src/xbt/RngStream.c
  src/xbt/automaton/automaton.c
  src/xbt/automaton/automatonparse_promela.c
  src/xbt/config.c
  src/xbt/cunit.c
  src/xbt/dict.c
  src/xbt/dict_cursor.c
  src/xbt/dict_elm.c
  src/xbt/dict_multi.c
  src/xbt/dynar.c
  src/xbt/ex.c
  src/xbt/fifo.c
  src/xbt/graph.c
  src/xbt/graphxml_parse.c
  src/xbt/heap.c
  src/xbt/lib.c
  src/xbt/log.c
  src/xbt/mallocator.c
  src/xbt/parmap.c
  src/xbt/set.c
  src/xbt/setset.c
  src/xbt/snprintf.c
  src/xbt/swag.c
  src/xbt/xbt_log_appender_file.c
  src/xbt/xbt_log_layout_format.c
  src/xbt/xbt_log_layout_simple.c
  src/xbt/xbt_main.c
  src/xbt/xbt_matrix.c
  src/xbt/xbt_os_time.c
  src/xbt/xbt_peer.c
  src/xbt/xbt_queue.c
  src/xbt/xbt_replay.c
  src/xbt/xbt_sg_synchro.c
  src/xbt/xbt_sha.c
  src/xbt/xbt_str.c
  src/xbt/xbt_strbuff.c
  src/xbt/xbt_virtu.c
  src/xbt_modinter.h
  )

if(HAVE_MMAP)
  set(XBT_SRC
    ${XBT_SRC}
    src/xbt/mmalloc/mm.c
    )
endif()

set(GTNETS_SRC
  src/surf/gtnets/gtnets_interface.cc
  src/surf/gtnets/gtnets_simulator.cc
  src/surf/gtnets/gtnets_topology.cc
  src/surf/network_gtnets.c
  )

set(NS3_SRC
  src/surf/network_ns3.c
  src/surf/ns3/my-point-to-point-helper.cc
  src/surf/ns3/ns3_interface.cc
  src/surf/ns3/ns3_simulator.cc
  src/surf/ns3/red-queue.cc
  )

set(SURF_SRC
  src/surf/cpu_cas01.c
  src/surf/cpu_ti.c
  src/surf/fair_bottleneck.c
  src/surf/lagrange.c
  src/surf/maxmin.c
  src/surf/network.c
  src/surf/network_constant.c
  src/surf/platf_generator.c
  src/surf/random_mgr.c
  src/surf/sg_platf.c
  src/surf/storage.c
  src/surf/surf.c
  src/surf/surf_action.c
  src/surf/surf_config.c
  src/surf/surf_model.c
  src/surf/surf_routing.c
  src/surf/surf_routing_cluster.c
  src/surf/surf_routing_dijkstra.c
  src/surf/surf_routing_floyd.c
  src/surf/surf_routing_full.c
  src/surf/surf_routing_generic.c
  src/surf/surf_routing_none.c
  src/surf/surf_routing_rulebased.c
  src/surf/surf_routing_vivaldi.c
  src/surf/surfxml_parse.c
  src/surf/surfxml_parseplatf.c
  src/surf/trace_mgr.c
  src/surf/workstation.c
  src/surf/workstation_ptask_L07.c
  src/xbt/xbt_sg_stubs.c
  )

set(SIMIX_SRC
  src/simix/smx_context.c
  src/simix/smx_context_base.c
  src/simix/smx_context_raw.c
  src/simix/smx_deployment.c
  src/simix/smx_environment.c
  src/simix/smx_global.c
  src/simix/smx_host.c
  src/simix/smx_io.c
  src/simix/smx_network.c
  src/simix/smx_process.c
  src/simix/smx_smurf.c
  src/simix/smx_synchro.c
  src/simix/smx_user.c
  )

set(MSG_SRC
  src/msg/msg_actions.c
  src/msg/msg_config.c
  src/msg/msg_deployment.c
  src/msg/msg_environment.c
  src/msg/msg_global.c
  src/msg/msg_gos.c
  src/msg/msg_host.c
  src/msg/msg_io.c
  src/msg/msg_mailbox.c
  src/msg/msg_process.c
  src/msg/msg_task.c
  src/msg/msg_vm.c
  )

#* ****************************************************************************************** *#
#* TUTORIAL: New API                                                                          *#

set(MSG_SRC
  ${MSG_SRC}
  src/msg/msg_new_api.c
  )
set(EXTRA_DIST
  ${EXTRA_DIST}
  src/simix/smx_new_api_private.h
  )
set(SIMIX_SRC
  ${SIMIX_SRC}
  src/simix/smx_new_api.c
)
#* ****************************************************************************************** *#

#* ****************************************************************************************** *#
#* TUTORIAL: New Model                                                                        *#

set(SURF_SRC
  ${SURF_SRC}
  src/surf/new_model.c
  )
set(EXTRA_DIST
  ${EXTRA_DIST}
  src/surf/new_model_private.h
  )
#* ****************************************************************************************** *#

set(SIMDAG_SRC
  src/simdag/sd_daxloader.c
  src/simdag/sd_global.c
  src/simdag/sd_link.c
  src/simdag/sd_task.c
  src/simdag/sd_workstation.c
  )
if(HAVE_GRAPHVIZ)
  set(SIMDAG_SRC
    ${SIMDAG_SRC} src/simdag/sd_dotloader.c
    )
else()
  set(EXTRA_DIST
    ${EXTRA_DIST} src/simdag/sd_dotloader.c
    )
endif()

set(BINDINGS_SRC
  src/bindings/bindings_global.c
  src/bindings/lua/lua_private.h
  src/bindings/lua/lua_state_cloner.h
  src/bindings/lua/lua_utils.h
  src/bindings/lua/simgrid_lua.h
  )

set(LUA_SRC
  src/bindings/lua/lua_comm.c
  src/bindings/lua/lua_host.c
  src/bindings/lua/lua_platf.c
  src/bindings/lua/lua_process.c
  src/bindings/lua/lua_state_cloner.c
  src/bindings/lua/lua_task.c
  src/bindings/lua/lua_utils.c
  src/bindings/lua/simgrid_lua.c
  )

set(TRACING_SRC
  src/instr/instr_config.c
  src/instr/instr_interface.c
  src/instr/instr_msg_process.c
  src/instr/instr_msg_task.c
  src/instr/instr_paje_containers.c
  src/instr/instr_paje_trace.c
  src/instr/instr_paje_header.c
  src/instr/instr_paje_types.c
  src/instr/instr_paje_values.c
  src/instr/instr_private.h
  src/instr/instr_resource_utilization.c
  src/instr/instr_routing.c
  src/instr/instr_smpi.c
  src/instr/instr_surf.c
  )

set(JEDULE_SRC
  include/instr/jedule/jedule_events.h
  include/instr/jedule/jedule_output.h
  include/instr/jedule/jedule_platform.h
  include/instr/jedule/jedule_sd_binding.h
  src/instr/jedule/jedule_events.c
  src/instr/jedule/jedule_output.c
  src/instr/jedule/jedule_platform.c
  src/instr/jedule/jedule_sd_binding.c
  )

set(MC_SRC
  src/mc/mc_checkpoint.c
  src/mc/mc_compare.c
  src/mc/mc_dpor.c
  src/mc/mc_global.c
  src/mc/mc_liveness.c
  src/mc/mc_memory.c
  src/mc/mc_private.h
  src/mc/mc_request.c
  src/mc/mc_state.c
  src/mc/memory_map.c
  )

set(headers_to_install
  include/instr/instr.h
  include/msg/datatypes.h
  include/msg/msg.h
  include/simdag/datatypes.h
  include/simdag/simdag.h
  include/simgrid/modelchecker.h
  include/simgrid/platf.h
  include/simgrid/platf_generator.h
  include/simgrid/simix.h
  include/smpi/mpi.h
  include/smpi/mpif.h
  include/smpi/smpi.h
  include/smpi/smpi_cocci.h
  include/surf/simgrid_dtd.h
  include/surf/surf_routing.h
  include/surf/surfxml_parse.h
  include/xbt.h
  include/xbt/RngStream.h
  include/xbt/asserts.h
  include/xbt/automaton.h
  include/xbt/config.h
  include/xbt/cunit.h
  include/xbt/dict.h
  include/xbt/dynar.h
  include/xbt/ex.h
  include/xbt/fifo.h
  include/xbt/file_stat.h
  include/xbt/function_types.h
  include/xbt/graph.h
  include/xbt/graphxml.h
  include/xbt/graphxml_parse.h
  include/xbt/hash.h
  include/xbt/heap.h
  include/xbt/lib.h
  include/xbt/log.h
  include/xbt/mallocator.h
  include/xbt/matrix.h
  include/xbt/misc.h
  include/xbt/mmalloc.h
  include/xbt/module.h
  include/xbt/parmap.h
  include/xbt/peer.h
  include/xbt/queue.h
  include/xbt/replay.h
  include/xbt/set.h
  include/xbt/setset.h
  include/xbt/str.h
  include/xbt/strbuff.h
  include/xbt/swag.h
  include/xbt/synchro_core.h
  include/xbt/sysdep.h
  include/xbt/virtu.h
  include/xbt/xbt_os_thread.h
  )
set(source_of_generated_headers
  include/simgrid_config.h.in
  include/smpi/smpif.h.in
  src/context_sysv_config.h.in)

### depend of some variables setted upper
# -->CONTEXT_THREADS CONTEXT_UCONTEXT
if(${CONTEXT_THREADS}) #pthread
  set(SURF_SRC
    ${SURF_SRC}
    src/simix/smx_context_thread.c
    src/xbt/xbt_os_thread.c
    )
else() # NOT pthread
  set(EXTRA_DIST
    ${EXTRA_DIST}
    src/simix/smx_context_thread.c
    src/xbt/xbt_os_thread.c
    )
endif()

if(${CONTEXT_UCONTEXT}) #ucontext
  set(SURF_SRC
    ${SURF_SRC}
    src/simix/smx_context_sysv.c
    )
else() # NOT ucontext
  set(EXTRA_DIST
    ${EXTRA_DIST}
    src/simix/smx_context_sysv.c
    )
endif()

# -->HAVE_GTNETS
if(HAVE_GTNETS)
  set(GTNETS_USED
    ${GTNETS_SRC}
    )
else()
  set(GTNETS_USED "")
  set(EXTRA_DIST
    ${EXTRA_DIST}
    ${GTNETS_SRC}
    )
endif()

### Simgrid Lib sources
set(simgrid_sources
  ${BINDINGS_SRC}
  ${GTNETS_USED}
  ${JEDULE_SRC}
  ${MSG_SRC}
  ${SIMDAG_SRC}
  ${SIMIX_SRC}
  ${SURF_SRC}
  ${TRACING_SRC}
  ${XBT_SRC}
  )

if(HAVE_MC)
  set(simgrid_sources
    ${simgrid_sources}
    ${MC_SRC}
    )
endif()

if(HAVE_NS3)
  set(simgrid_sources
    ${simgrid_sources}
    ${NS3_SRC}
    )
endif()

# WINDOWS
if(WIN32)
  set(simgrid_sources
    ${simgrid_sources}
    src/simix/smx_context_thread.c
    src/xbt/win32_ucontext.c
    src/xbt/xbt_os_thread.c
    )
endif()

if(${HAVE_LUA})
  set(simgrid_sources
    ${simgrid_sources}
    ${LUA_SRC}
    )
else()
  set(EXTRA_DIST
    ${EXTRA_DIST}
    ${LUA_SRC}
    )
endif()

set(DOC_SOURCES
  doc/AS_hierarchy.png
  doc/sg_thread_model.fig
  doc/simix.fig
  doc/surf_nutshell.fig
  doc/Doxyfile.in
  doc/Layout.xml
  doc/triva-graph_configuration.png
  doc/triva-graph_visualization.png
  doc/triva-time_interval.png
  
    doc/doxygen/footer.html
  doc/doxygen/header.html
  doc/doxygen/stylesheet.css
  
  doc/doxygen/index.doc
  doc/doxygen/getting_started.doc  
  doc/doxygen/introduction.doc
  doc/doxygen/use.doc
  doc/doxygen/bindings.doc
  doc/doxygen/deployment.doc
  doc/doxygen/install.doc
  doc/doxygen/options.doc
  doc/doxygen/platform.doc
  doc/doxygen/pls.doc
  doc/doxygen/tracing.doc
  doc/doxygen/FAQ.doc
  doc/doxygen/advanced.doc
    doc/doxygen/inside_autotests.doc  
    doc/doxygen/inside_cmake.doc
    doc/doxygen/inside_extending.doc 
    doc/doxygen/inside_release.doc
    doc/doxygen/contributing.doc
  doc/doxygen/modules.doc
    doc/doxygen/module-msg.doc
    doc/doxygen/module-sd.doc
    doc/doxygen/module-simix.doc
    doc/doxygen/module-surf.doc
    doc/doxygen/module-trace.doc
    doc/doxygen/module-xbt.doc

  )

set(DOC_FIGS
  ${CMAKE_HOME_DIRECTORY}/doc/shared/fig/simgrid_modules.fig
  ${CMAKE_HOME_DIRECTORY}/doc/shared/fig/simgrid_modules2.fig
  )
  
set(DOC_TOOLS
  tools/doxygen/fig2dev_postprocessor.pl
  tools/doxygen/index_create.pl
  tools/doxygen/xbt_log_extract_hierarchy.pl
  )

# these files get copied automatically to the html documentation
set(DOC_IMG
  ${CMAKE_HOME_DIRECTORY}/doc/simgrid.css
  ${CMAKE_HOME_DIRECTORY}/doc/webcruft/Paje_MSG_screenshot.jpg
  ${CMAKE_HOME_DIRECTORY}/doc/webcruft/Paje_MSG_screenshot_thn.jpg
  ${CMAKE_HOME_DIRECTORY}/doc/webcruft/SGicon.gif
  ${CMAKE_HOME_DIRECTORY}/doc/webcruft/SGicon.icns
  ${CMAKE_HOME_DIRECTORY}/doc/webcruft/SGicon.ico
  ${CMAKE_HOME_DIRECTORY}/doc/webcruft/awstats_logo3.png
  ${CMAKE_HOME_DIRECTORY}/doc/webcruft/output.goal.pdf
  ${CMAKE_HOME_DIRECTORY}/doc/webcruft/poster_thumbnail.png
  ${CMAKE_HOME_DIRECTORY}/doc/webcruft/simgrid_logo_2011.gif
  ${CMAKE_HOME_DIRECTORY}/doc/webcruft/simgrid_logo_2011.png
  ${CMAKE_HOME_DIRECTORY}/doc/webcruft/simgrid_logo_2011_small.png
  ${CMAKE_HOME_DIRECTORY}/doc/webcruft/simgrid_logo_win.bmp
  ${CMAKE_HOME_DIRECTORY}/doc/webcruft/simgrid_logo_win_2011.bmp
  ${CMAKE_HOME_DIRECTORY}/doc/webcruft/win_install_01.png
  ${CMAKE_HOME_DIRECTORY}/doc/webcruft/win_install_02.png
  ${CMAKE_HOME_DIRECTORY}/doc/webcruft/win_install_03.png
  ${CMAKE_HOME_DIRECTORY}/doc/webcruft/win_install_04.png
  ${CMAKE_HOME_DIRECTORY}/doc/webcruft/win_install_05.png
  ${CMAKE_HOME_DIRECTORY}/doc/webcruft/win_install_06.png
  )

set(bin_files
  ${bin_files}
  src/smpi/smpicc.in
  src/smpi/smpif2c.in
  src/smpi/smpiff.in
  src/smpi/smpif90.in
  src/smpi/smpirun.in
  )

set(txt_files
  ${txt_files}
  AUTHORS
  COPYING
  ChangeLog
  INSTALL
  LICENSE-LGPL-2.1
  NEWS
  TODO
  configure
  )

set(EXAMPLES_CMAKEFILES_TXT
  examples/lua/CMakeLists.txt
  examples/msg/CMakeLists.txt
  examples/msg/actions/CMakeLists.txt
  examples/msg/bittorrent/CMakeLists.txt
  examples/msg/chord/CMakeLists.txt
  examples/msg/cloud/CMakeLists.txt
  examples/msg/gpu/CMakeLists.txt
  examples/msg/gtnets/CMakeLists.txt
  examples/msg/icomms/CMakeLists.txt
  examples/msg/io/CMakeLists.txt
  examples/msg/kademlia/CMakeLists.txt
  examples/msg/masterslave/CMakeLists.txt
  examples/msg/mc/CMakeLists.txt
  examples/msg/migration/CMakeLists.txt
  examples/msg/ns3/CMakeLists.txt
  examples/msg/parallel_task/CMakeLists.txt
  examples/msg/pmm/CMakeLists.txt
  examples/msg/priority/CMakeLists.txt
  examples/msg/properties/CMakeLists.txt
  examples/msg/sendrecv/CMakeLists.txt
  examples/msg/chainsend/CMakeLists.txt
  examples/msg/start_kill_time/CMakeLists.txt
  examples/msg/suspend/CMakeLists.txt
  examples/msg/token_ring/CMakeLists.txt
  examples/msg/tracing/CMakeLists.txt
  examples/simdag/CMakeLists.txt
  examples/simdag/dax/CMakeLists.txt
  examples/simdag/dot/CMakeLists.txt
  examples/simdag/goal/CMakeLists.txt
  examples/simdag/metaxml/CMakeLists.txt
  examples/simdag/properties/CMakeLists.txt
  examples/simdag/scheduling/CMakeLists.txt
  examples/smpi/CMakeLists.txt
  examples/smpi/MM/CMakeLists.txt
  examples/xbt/CMakeLists.txt
  )

set(TESHSUITE_CMAKEFILES_TXT
  teshsuite/CMakeLists.txt
  teshsuite/msg/CMakeLists.txt
  teshsuite/msg/trace/CMakeLists.txt
  teshsuite/simdag/CMakeLists.txt
  teshsuite/simdag/network/CMakeLists.txt
  teshsuite/simdag/network/mxn/CMakeLists.txt
  teshsuite/simdag/network/p2p/CMakeLists.txt
  teshsuite/simdag/partask/CMakeLists.txt
  teshsuite/simdag/platforms/CMakeLists.txt
  teshsuite/xbt/CMakeLists.txt
  teshsuite/smpi/CMakeLists.txt
  teshsuite/smpi/mpich-test/env/CMakeLists.txt
  teshsuite/smpi/mpich-test/coll/CMakeLists.txt
  teshsuite/smpi/mpich-test/context/CMakeLists.txt
  teshsuite/smpi/mpich-test/profile/CMakeLists.txt
  teshsuite/smpi/mpich-test/pt2pt/CMakeLists.txt
  )

set(TOOLS_CMAKEFILES_TXT
  tools/CMakeLists.txt
  tools/graphicator/CMakeLists.txt
  tools/tesh/CMakeLists.txt
  )

set(TESTSUITE_CMAKEFILES_TXT
  testsuite/surf/CMakeLists.txt
  testsuite/xbt/CMakeLists.txt
  )

set(CMAKE_SOURCE_FILES
  CMakeLists.txt
  buildtools/Cmake/AddTests.cmake
  buildtools/Cmake/CTestConfig.cmake
  buildtools/Cmake/CTestCustom.cmake
  buildtools/Cmake/CompleteInFiles.cmake
  buildtools/Cmake/DefinePackages.cmake
  buildtools/Cmake/Distrib.cmake
  buildtools/Cmake/Flags.cmake
  buildtools/Cmake/GenerateDoc.cmake
  buildtools/Cmake/GenerateDocWin.cmake
  buildtools/Cmake/MaintainerMode.cmake
  buildtools/Cmake/MakeExe.cmake
  buildtools/Cmake/MakeLib.cmake
  buildtools/Cmake/MakeLibWin.cmake
  buildtools/Cmake/Modules/FindF2c.cmake
  buildtools/Cmake/Modules/FindGTnets.cmake
  buildtools/Cmake/Modules/FindGraphviz.cmake
  buildtools/Cmake/Modules/FindLua51Simgrid.cmake
  buildtools/Cmake/Modules/FindNS3.cmake
  buildtools/Cmake/Modules/FindPCRE.cmake
  buildtools/Cmake/Modules/FindPcreWin.cmake
  buildtools/Cmake/Modules/FindRngStream.cmake
  buildtools/Cmake/Modules/FindRubySimgrid.cmake
  buildtools/Cmake/Modules/FindSimGrid.cmake
  buildtools/Cmake/Modules/FindValgrind.cmake
  buildtools/Cmake/Modules/FindLibunwind.cmake
  buildtools/Cmake/Option.cmake
  buildtools/Cmake/Pipol.cmake
  buildtools/Cmake/PrintArgs.cmake
  buildtools/Cmake/Scripts/Diff.pm
  buildtools/Cmake/Scripts/Makefile.default
  buildtools/Cmake/Scripts/SimGrid.packproj
  buildtools/Cmake/Scripts/generate_memcheck_tests.pl
  buildtools/Cmake/Scripts/generate_new_tests.pl
  buildtools/Cmake/Scripts/my_valgrind.pl
  buildtools/Cmake/Scripts/postinstall.sh
  buildtools/Cmake/Scripts/preinstall.sh
  buildtools/Cmake/Scripts/tesh.pl
  buildtools/Cmake/Scripts/test_java.sh
  buildtools/Cmake/Scripts/update_tesh.pl
  buildtools/Cmake/Supernovae.cmake
  buildtools/Cmake/UnitTesting.cmake
  buildtools/Cmake/src/internal_config.h.in
  buildtools/Cmake/src/simgrid.nsi.in
  buildtools/Cmake/test_prog/prog_AC_CHECK_MCSC.c
  buildtools/Cmake/test_prog/prog_getline.c
  buildtools/Cmake/test_prog/prog_mutex_timedlock.c
  buildtools/Cmake/test_prog/prog_printf_null.c
  buildtools/Cmake/test_prog/prog_sem_init.c
  buildtools/Cmake/test_prog/prog_sem_open.c
  buildtools/Cmake/test_prog/prog_sem_timedwait.c
  buildtools/Cmake/test_prog/prog_snprintf.c
  buildtools/Cmake/test_prog/prog_stackgrowth.c
  buildtools/Cmake/test_prog/prog_stacksetup.c
  buildtools/Cmake/test_prog/prog_thread_storage.c
  buildtools/Cmake/test_prog/prog_va_copy.c
  buildtools/Cmake/test_prog/prog_vsnprintf.c
  )

set(PLATFORMS_EXAMPLES
  examples/platforms/bypassASroute.xml
  examples/platforms/bypassRoute.xml
  examples/platforms/cloud.xml
  examples/platforms/cluster.xml
  examples/platforms/cluster_and_one_host.xml
  examples/platforms/cluster_no_backbone.xml
  examples/platforms/cluster_routing_rulebased.xml
  examples/platforms/clusters_routing_full.xml
  examples/platforms/conf/gridpp_grid_2004.conf
  examples/platforms/conf/gridpp_grid_2004.xml
  examples/platforms/conf/lcg_sept2004_grid.conf
  examples/platforms/conf/lcg_sept2004_grid.xml
  examples/platforms/conf/transform_optorsim_platform.pl
  examples/platforms/config.xml
  examples/platforms/content/storage_content.txt
  examples/platforms/data_center.xml
  examples/platforms/g5k.xml
  examples/platforms/generation_scripts/create_hierarchical_clusters.pl
  examples/platforms/generation_scripts/enhancedDTDwithHierarchicalCluster.pl
  examples/platforms/generation_scripts/generate_g5k_platform.pl
  examples/platforms/generation_scripts/generate_g5k_platform_cabinets.pl
  examples/platforms/griffon.xml
  examples/platforms/multicore_machine.xml
  examples/platforms/prop.xml
  examples/platforms/storage.xml
  examples/platforms/syscoord/generate_peer_platform.pl
  examples/platforms/syscoord/median_harvard.syscoord
  examples/platforms/syscoord/median_harvard.xml
  examples/platforms/syscoord/median_meridian.syscoord
  examples/platforms/syscoord/median_meridian.xml
  examples/platforms/syscoord/median_p2psim.syscoord
  examples/platforms/syscoord/median_p2psim.xml
  examples/platforms/vivaldi.xml
  examples/platforms/routing_cluster.xml
  examples/platforms/meta_cluster.xml
  examples/platforms/two_peers.xml
  )

set(generated_src_files
  src/xbt/automaton/automaton_lexer.yy.c
  src/xbt/automaton/parserPromela.tab.cacc
  src/xbt/automaton/parserPromela.tab.hacc
  )

foreach(file ${generated_src_files})
  set_source_files_properties(${file} PROPERTIES GENERATED true)
endforeach(file ${generated_src_files})
