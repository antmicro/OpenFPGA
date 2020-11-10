#ifndef TILE_ANNOTATION_H
#define TILE_ANNOTATION_H

/********************************************************************
 * Include header files required by the data structure definition
 *******************************************************************/
#include <vector>
#include <map>
#include <array>

#include "vtr_vector.h"

#include "openfpga_port.h"

#include "tile_annotation_fwd.h"

/* namespace openfpga begins */
namespace openfpga {

/********************************************************************
 * This file include the declaration of data structures
 * to store physical tile annotation, including
 * 1. global port definition where a tile port can be treated as a 
 *    global port of the FPGA fabric
 *
 * Note:
 * 1. Keep this data structure as general as possible. It is supposed
 *    to contain the raw data from architecture XML! If you want to link
 *    to other data structures, please create another one in other header files
 *******************************************************************/
class TileAnnotation {
  public: /* Types */
    typedef vtr::vector<TileGlobalPortId, TileGlobalPortId>::const_iterator global_port_iterator;
    /* Create range */
    typedef vtr::Range<global_port_iterator> global_port_range;
  public:  /* Constructor */
    TileAnnotation();
  public:  /* Public accessors: aggregators */
    global_port_range global_ports() const;
  public:  /* Public accessors */
    std::string global_port_name(const TileGlobalPortId& global_port_id) const;
    std::string global_port_tile_name(const TileGlobalPortId& global_port_id) const;
    BasicPort global_port_tile_port(const TileGlobalPortId& global_port_id) const;
    bool global_port_is_clock(const TileGlobalPortId& global_port_id) const;
    bool global_port_is_set(const TileGlobalPortId& global_port_id) const;
    bool global_port_is_reset(const TileGlobalPortId& global_port_id) const;
    size_t global_port_default_value(const TileGlobalPortId& global_port_id) const;
  public: /* Public mutators */
    /* By default, we do not set it as a clock.
     * Users should set it through the set_global_port_is_clock() function
     */
    TileGlobalPortId create_global_port(const std::string& port_name,
                                        const std::string& tile_name,
                                        const BasicPort& tile_port);
    void set_global_port_is_clock(const TileGlobalPortId& global_port_id,
                                  const bool& is_clock);
    void set_global_port_is_set(const TileGlobalPortId& global_port_id,
                                const bool& is_set);
    void set_global_port_is_reset(const TileGlobalPortId& global_port_id,
                                  const bool& is_reset);
    void set_global_port_default_value(const TileGlobalPortId& global_port_id,
                                       const size_t& default_value);
  public: /* Public validator */
    bool valid_global_port_id(const TileGlobalPortId& global_port_id) const;
  private: /* Internal data */
    /* Global port information for tiles */
    vtr::vector<TileGlobalPortId, TileGlobalPortId> global_port_ids_;
    vtr::vector<TileGlobalPortId, std::string> global_port_names_;
    vtr::vector<TileGlobalPortId, std::string> global_port_tile_names_;
    vtr::vector<TileGlobalPortId, BasicPort> global_port_tile_ports_;
    vtr::vector<TileGlobalPortId, bool> global_port_is_clock_;
    vtr::vector<TileGlobalPortId, bool> global_port_is_reset_;
    vtr::vector<TileGlobalPortId, bool> global_port_is_set_;
    vtr::vector<TileGlobalPortId, size_t> global_port_default_values_;
};

} /* namespace openfpga ends */

#endif
