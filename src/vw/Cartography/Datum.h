// __BEGIN_LICENSE__
// 
// Copyright (C) 2006 United States Government as represented by the
// Administrator of the National Aeronautics and Space Administration
// (NASA).  All Rights Reserved.
// 
// Copyright 2006 Carnegie Mellon University. All rights reserved.
// 
// This software is distributed under the NASA Open Source Agreement
// (NOSA), version 1.3.  The NOSA has been approved by the Open Source
// Initiative.  See the file COPYING at the top of the distribution
// directory tree for the complete NOSA document.
// 
// THE SUBJECT SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY OF ANY
// KIND, EITHER EXPRESSED, IMPLIED, OR STATUTORY, INCLUDING, BUT NOT
// LIMITED TO, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL CONFORM TO
// SPECIFICATIONS, ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR
// A PARTICULAR PURPOSE, OR FREEDOM FROM INFRINGEMENT, ANY WARRANTY THAT
// THE SUBJECT SOFTWARE WILL BE ERROR FREE, OR ANY WARRANTY THAT
// DOCUMENTATION, IF PROVIDED, WILL CONFORM TO THE SUBJECT SOFTWARE.
// 
// __END_LICENSE__
#ifndef __VW_CARTOGRAPHY_DATUM_H__
#define __VW_CARTOGRAPHY_DATUM_H__

#include <string>
#include <ostream>
#include <math.h>

#include <vw/Math/Vector.h>
#include <vw/Image/PerPixelViews.h>

// For an excellent discussion of the various concepts, terms, and 
// issues involved in global coordinate systems, see:
// http://www.posc.org/Epicentre.2_2/DataModel/ExamplesofUsage/eu_cs.html

namespace vw {
namespace cartography {

  /// A geodetic datum, i.e. a reference ellipsoid coordinate system
  /// for a planetary body.  This implementation assumes a relatively
  /// modern notion of a datum, ie. a geocentric bi-axial ellipsoidal 
  /// model.
  ///
  /// To express a spherical datum, set the semi-major axis equal to
  /// the semi-minor axis.  All angles are measured in degrees, and
  /// all distances are measured in meters.  This class incorporates a
  /// prime meridian offset, which is not usually strictly considered
  /// part of the datum but which has no better place to be right now.
  class Datum {
    std::string m_name;
    std::string m_spheroid_name;
    std::string m_meridian_name;
    double m_semi_major_axis;
    double m_semi_minor_axis;
    double m_meridian_offset;
    std::string m_proj_str;

  public:
    /// The default constructor creates a WGS84 datum.
    Datum() {
      set_well_known_datum("WGS84");
    }

    /// Constructs a well-known datum by name.
    Datum( std::string const& name ) {
      set_well_known_datum( name );
    }

    /// This constructor allows the user to create a custom datum.
    Datum(std::string const& name,
          std::string const& spheroid_name,
          std::string const& meridian_name,
          double semi_major_axis,
          double semi_minor_axis,
          double meridian_offset);

    /// Options include: WGS84, WGS72, NAD27, or NAD83. 
    void set_well_known_datum(std::string const& name);
   
    std::string &name() { return m_name; }
    std::string const& name() const { return m_name; }

    std::string &spheroid_name() { return m_spheroid_name; }
    std::string const& spheroid_name() const { return m_spheroid_name; }

    std::string &meridian_name() { return m_meridian_name; }
    std::string const& meridian_name() const { return m_meridian_name; }

    void set_semi_major_axis(double val);
    double const& semi_major_axis() const { return m_semi_major_axis; }

    void set_semi_minor_axis(double val);
    double const &semi_minor_axis() const { return m_semi_minor_axis; }

    double &meridian_offset() { return m_meridian_offset; }
    double const& meridian_offset() const { return m_meridian_offset; }


    std::string proj4_str() const { return m_proj_str; }

    double radius(double lon, double lat) const;

    double inverse_flattening() const;

    Vector3 geodetic_to_cartesian( Vector3 const& p ) const;
    Vector3 cartesian_to_geodetic( Vector3 const& p ) const;
  };

  std::ostream& operator<<(std::ostream& os, const Datum& datum);


}} // namespace vw::cartography

#endif // __VW_CARTOGRAPHY_DATUM_H__

