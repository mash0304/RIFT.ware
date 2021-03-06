/* geocode-glib-1.0.vapi generated by vapigen, do not modify. */

[CCode (cprefix = "Geocode", gir_namespace = "GeocodeGlib", gir_version = "1.0", lower_case_cprefix = "geocode_")]
namespace Geocode {
	namespace LocationAccuracy {
		[CCode (cheader_filename = "geocode-glib/geocode-glib.h", cname = "GEOCODE_LOCATION_ACCURACY_CITY")]
		public const int CITY;
		[CCode (cheader_filename = "geocode-glib/geocode-glib.h", cname = "GEOCODE_LOCATION_ACCURACY_CONTINENT")]
		public const int CONTINENT;
		[CCode (cheader_filename = "geocode-glib/geocode-glib.h", cname = "GEOCODE_LOCATION_ACCURACY_COUNTRY")]
		public const int COUNTRY;
		[CCode (cheader_filename = "geocode-glib/geocode-glib.h", cname = "GEOCODE_LOCATION_ACCURACY_REGION")]
		public const int REGION;
		[CCode (cheader_filename = "geocode-glib/geocode-glib.h", cname = "GEOCODE_LOCATION_ACCURACY_STREET")]
		public const int STREET;
		[CCode (cheader_filename = "geocode-glib/geocode-glib.h", cname = "GEOCODE_LOCATION_ACCURACY_UNKNOWN")]
		public const int UNKNOWN;
	}
	[CCode (cheader_filename = "geocode-glib/geocode-glib.h", type_id = "geocode_forward_get_type ()")]
	public class Forward : GLib.Object {
		[CCode (has_construct_function = false)]
		protected Forward ();
		[CCode (has_construct_function = false)]
		public Forward.for_params (GLib.HashTable<string,GLib.Value?> @params);
		[CCode (has_construct_function = false)]
		public Forward.for_string (string str);
		public GLib.List<weak Geocode.Place> search () throws GLib.Error;
		public async GLib.List<weak Geocode.Place> search_async (GLib.Cancellable? cancellable = null) throws GLib.Error;
		public void set_answer_count (uint count);
	}
	[CCode (cheader_filename = "geocode-glib/geocode-glib.h", type_id = "geocode_location_get_type ()")]
	public class Location : GLib.Object {
		[CCode (has_construct_function = false)]
		public Location (double latitude, double longitude, double accuracy = LocationAccuracy.UNKNOWN);
		public double get_accuracy ();
		public unowned string get_description ();
		public double get_distance_from (Geocode.Location locb);
		public double get_latitude ();
		public double get_longitude ();
		public uint64 get_timestamp ();
		public void set_description (string description);
		[CCode (has_construct_function = false)]
		public Location.with_description (double latitude, double longitude, double accuracy, string description);
		public double accuracy { get; construct; }
		public string description { get; set; }
		public double latitude { get; construct; }
		public double longitude { get; construct; }
		public uint64 timestamp { get; }
	}
	[CCode (cheader_filename = "geocode-glib/geocode-glib.h", type_id = "geocode_place_get_type ()")]
	public class Place : GLib.Object {
		[CCode (has_construct_function = false)]
		public Place (string name, Geocode.PlaceType place_type);
		public unowned string get_administrative_area ();
		public unowned string get_area ();
		public unowned string get_building ();
		public unowned string get_continent ();
		public unowned string get_country ();
		public unowned string get_country_code ();
		public unowned string get_county ();
		public unowned GLib.Icon get_icon ();
		public unowned Geocode.Location get_location ();
		public unowned string get_name ();
		public Geocode.PlaceType get_place_type ();
		public unowned string get_postal_code ();
		public unowned string get_state ();
		public unowned string get_street ();
		public unowned string get_street_address ();
		public unowned string get_town ();
		public void set_administrative_area (string admin_area);
		public void set_area (string area);
		public void set_building (string building);
		public void set_continent (string continent);
		public void set_country (string country);
		public void set_country_code (string country_code);
		public void set_county (string county);
		public void set_location (Geocode.Location location);
		public void set_name (string name);
		public void set_postal_code (string postal_code);
		public void set_state (string state);
		public void set_street (string street);
		public void set_street_address (string street_address);
		public void set_town (string town);
		[CCode (has_construct_function = false)]
		public Place.with_location (string name, Geocode.PlaceType place_type, Geocode.Location location);
		public string administrative_area { get; set; }
		public string area { get; set; }
		public string building { get; set; }
		public string continent { get; set; }
		public string country { get; set; }
		public string country_code { get; set; }
		public string county { get; set; }
		[NoAccessorMethod]
		public GLib.Icon icon { owned get; set; }
		public Geocode.Location location { get; set; }
		public string name { get; set; }
		public Geocode.PlaceType place_type { get; construct; }
		public string postal_code { get; set; }
		public string state { get; set; }
		public string street { get; set; }
		public string street_address { get; set; }
		public string town { get; set; }
	}
	[CCode (cheader_filename = "geocode-glib/geocode-glib.h", type_id = "geocode_reverse_get_type ()")]
	public class Reverse : GLib.Object {
		[CCode (has_construct_function = false)]
		protected Reverse ();
		[CCode (has_construct_function = false)]
		public Reverse.for_location (Geocode.Location location);
		public Geocode.Place resolve () throws GLib.Error;
		public async Geocode.Place resolve_async (GLib.Cancellable? cancellable = null) throws GLib.Error;
	}
	[CCode (cheader_filename = "geocode-glib/geocode-glib.h", cprefix = "GEOCODE_PLACE_TYPE_", type_id = "geocode_place_type_get_type ()")]
	public enum PlaceType {
		UNKNOWN,
		BUILDING,
		STREET,
		TOWN,
		STATE,
		COUNTY,
		LOCAL_ADMINISTRATIVE_AREA,
		POSTAL_CODE,
		COUNTRY,
		ISLAND,
		AIRPORT,
		RAILWAY_STATION,
		BUS_STOP,
		MOTORWAY,
		DRAINAGE,
		LAND_FEATURE,
		MISCELLANEOUS,
		SUPERNAME,
		POINT_OF_INTEREST,
		SUBURB,
		COLLOQUIAL,
		ZONE,
		HISTORICAL_STATE,
		HISTORICAL_COUNTY,
		CONTINENT,
		TIME_ZONE,
		ESTATE,
		HISTORICAL_TOWN,
		OCEAN,
		SEA
	}
	[CCode (cheader_filename = "geocode-glib/geocode-glib.h", cprefix = "GEOCODE_ERROR_")]
	public errordomain Error {
		PARSE,
		NOT_SUPPORTED,
		NO_MATCHES,
		INVALID_ARGUMENTS,
		INTERNAL_SERVER;
		public static GLib.Quark quark ();
	}
}
