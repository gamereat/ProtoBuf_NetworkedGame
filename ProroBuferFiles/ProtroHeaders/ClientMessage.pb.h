// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ClientMessage.proto

#ifndef PROTOBUF_ClientMessage_2eproto__INCLUDED
#define PROTOBUF_ClientMessage_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace ClientMessage {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ClientMessage_2eproto();
void protobuf_AssignDesc_ClientMessage_2eproto();
void protobuf_ShutdownFile_ClientMessage_2eproto();

class ClientInformation;
class playerPos;
class Playerinfromation;
class ClientMessage;

enum Playerinfromation_PlayerType {
  Playerinfromation_PlayerType_PacMan = 1,
  Playerinfromation_PlayerType_Ghost = 2,
  Playerinfromation_PlayerType_Unassigned = 3
};
bool Playerinfromation_PlayerType_IsValid(int value);
const Playerinfromation_PlayerType Playerinfromation_PlayerType_PlayerType_MIN = Playerinfromation_PlayerType_PacMan;
const Playerinfromation_PlayerType Playerinfromation_PlayerType_PlayerType_MAX = Playerinfromation_PlayerType_Unassigned;
const int Playerinfromation_PlayerType_PlayerType_ARRAYSIZE = Playerinfromation_PlayerType_PlayerType_MAX + 1;

const ::google::protobuf::EnumDescriptor* Playerinfromation_PlayerType_descriptor();
inline const ::std::string& Playerinfromation_PlayerType_Name(Playerinfromation_PlayerType value) {
  return ::google::protobuf::internal::NameOfEnum(
    Playerinfromation_PlayerType_descriptor(), value);
}
inline bool Playerinfromation_PlayerType_Parse(
    const ::std::string& name, Playerinfromation_PlayerType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Playerinfromation_PlayerType>(
    Playerinfromation_PlayerType_descriptor(), name, value);
}
enum ClientMessage_AdditioanlRequests {
  ClientMessage_AdditioanlRequests_None = 1,
  ClientMessage_AdditioanlRequests_FirstConnect = 2,
  ClientMessage_AdditioanlRequests_Reconnect = 3,
  ClientMessage_AdditioanlRequests_Disconnect = 4
};
bool ClientMessage_AdditioanlRequests_IsValid(int value);
const ClientMessage_AdditioanlRequests ClientMessage_AdditioanlRequests_AdditioanlRequests_MIN = ClientMessage_AdditioanlRequests_None;
const ClientMessage_AdditioanlRequests ClientMessage_AdditioanlRequests_AdditioanlRequests_MAX = ClientMessage_AdditioanlRequests_Disconnect;
const int ClientMessage_AdditioanlRequests_AdditioanlRequests_ARRAYSIZE = ClientMessage_AdditioanlRequests_AdditioanlRequests_MAX + 1;

const ::google::protobuf::EnumDescriptor* ClientMessage_AdditioanlRequests_descriptor();
inline const ::std::string& ClientMessage_AdditioanlRequests_Name(ClientMessage_AdditioanlRequests value) {
  return ::google::protobuf::internal::NameOfEnum(
    ClientMessage_AdditioanlRequests_descriptor(), value);
}
inline bool ClientMessage_AdditioanlRequests_Parse(
    const ::std::string& name, ClientMessage_AdditioanlRequests* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ClientMessage_AdditioanlRequests>(
    ClientMessage_AdditioanlRequests_descriptor(), name, value);
}
// ===================================================================

class ClientInformation : public ::google::protobuf::Message {
 public:
  ClientInformation();
  virtual ~ClientInformation();

  ClientInformation(const ClientInformation& from);

  inline ClientInformation& operator=(const ClientInformation& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ClientInformation& default_instance();

  void Swap(ClientInformation* other);

  // implements Message ----------------------------------------------

  ClientInformation* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ClientInformation& from);
  void MergeFrom(const ClientInformation& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 clientVersion = 1;
  inline bool has_clientversion() const;
  inline void clear_clientversion();
  static const int kClientVersionFieldNumber = 1;
  inline ::google::protobuf::int32 clientversion() const;
  inline void set_clientversion(::google::protobuf::int32 value);

  // required int64 messageNumber = 2;
  inline bool has_messagenumber() const;
  inline void clear_messagenumber();
  static const int kMessageNumberFieldNumber = 2;
  inline ::google::protobuf::int64 messagenumber() const;
  inline void set_messagenumber(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:ClientMessage.ClientInformation)
 private:
  inline void set_has_clientversion();
  inline void clear_has_clientversion();
  inline void set_has_messagenumber();
  inline void clear_has_messagenumber();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int64 messagenumber_;
  ::google::protobuf::int32 clientversion_;
  friend void  protobuf_AddDesc_ClientMessage_2eproto();
  friend void protobuf_AssignDesc_ClientMessage_2eproto();
  friend void protobuf_ShutdownFile_ClientMessage_2eproto();

  void InitAsDefaultInstance();
  static ClientInformation* default_instance_;
};
// -------------------------------------------------------------------

class playerPos : public ::google::protobuf::Message {
 public:
  playerPos();
  virtual ~playerPos();

  playerPos(const playerPos& from);

  inline playerPos& operator=(const playerPos& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const playerPos& default_instance();

  void Swap(playerPos* other);

  // implements Message ----------------------------------------------

  playerPos* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const playerPos& from);
  void MergeFrom(const playerPos& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required float posY = 1;
  inline bool has_posy() const;
  inline void clear_posy();
  static const int kPosYFieldNumber = 1;
  inline float posy() const;
  inline void set_posy(float value);

  // required float posX = 2;
  inline bool has_posx() const;
  inline void clear_posx();
  static const int kPosXFieldNumber = 2;
  inline float posx() const;
  inline void set_posx(float value);

  // @@protoc_insertion_point(class_scope:ClientMessage.playerPos)
 private:
  inline void set_has_posy();
  inline void clear_has_posy();
  inline void set_has_posx();
  inline void clear_has_posx();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  float posy_;
  float posx_;
  friend void  protobuf_AddDesc_ClientMessage_2eproto();
  friend void protobuf_AssignDesc_ClientMessage_2eproto();
  friend void protobuf_ShutdownFile_ClientMessage_2eproto();

  void InitAsDefaultInstance();
  static playerPos* default_instance_;
};
// -------------------------------------------------------------------

class Playerinfromation : public ::google::protobuf::Message {
 public:
  Playerinfromation();
  virtual ~Playerinfromation();

  Playerinfromation(const Playerinfromation& from);

  inline Playerinfromation& operator=(const Playerinfromation& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Playerinfromation& default_instance();

  void Swap(Playerinfromation* other);

  // implements Message ----------------------------------------------

  Playerinfromation* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Playerinfromation& from);
  void MergeFrom(const Playerinfromation& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef Playerinfromation_PlayerType PlayerType;
  static const PlayerType PacMan = Playerinfromation_PlayerType_PacMan;
  static const PlayerType Ghost = Playerinfromation_PlayerType_Ghost;
  static const PlayerType Unassigned = Playerinfromation_PlayerType_Unassigned;
  static inline bool PlayerType_IsValid(int value) {
    return Playerinfromation_PlayerType_IsValid(value);
  }
  static const PlayerType PlayerType_MIN =
    Playerinfromation_PlayerType_PlayerType_MIN;
  static const PlayerType PlayerType_MAX =
    Playerinfromation_PlayerType_PlayerType_MAX;
  static const int PlayerType_ARRAYSIZE =
    Playerinfromation_PlayerType_PlayerType_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  PlayerType_descriptor() {
    return Playerinfromation_PlayerType_descriptor();
  }
  static inline const ::std::string& PlayerType_Name(PlayerType value) {
    return Playerinfromation_PlayerType_Name(value);
  }
  static inline bool PlayerType_Parse(const ::std::string& name,
      PlayerType* value) {
    return Playerinfromation_PlayerType_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // required int32 playerNumber = 1;
  inline bool has_playernumber() const;
  inline void clear_playernumber();
  static const int kPlayerNumberFieldNumber = 1;
  inline ::google::protobuf::int32 playernumber() const;
  inline void set_playernumber(::google::protobuf::int32 value);

  // required .ClientMessage.Playerinfromation.PlayerType type = 2 [default = Unassigned];
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 2;
  inline ::ClientMessage::Playerinfromation_PlayerType type() const;
  inline void set_type(::ClientMessage::Playerinfromation_PlayerType value);

  // required .ClientMessage.playerPos pos = 3;
  inline bool has_pos() const;
  inline void clear_pos();
  static const int kPosFieldNumber = 3;
  inline const ::ClientMessage::playerPos& pos() const;
  inline ::ClientMessage::playerPos* mutable_pos();
  inline ::ClientMessage::playerPos* release_pos();
  inline void set_allocated_pos(::ClientMessage::playerPos* pos);

  // @@protoc_insertion_point(class_scope:ClientMessage.Playerinfromation)
 private:
  inline void set_has_playernumber();
  inline void clear_has_playernumber();
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_pos();
  inline void clear_has_pos();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int32 playernumber_;
  int type_;
  ::ClientMessage::playerPos* pos_;
  friend void  protobuf_AddDesc_ClientMessage_2eproto();
  friend void protobuf_AssignDesc_ClientMessage_2eproto();
  friend void protobuf_ShutdownFile_ClientMessage_2eproto();

  void InitAsDefaultInstance();
  static Playerinfromation* default_instance_;
};
// -------------------------------------------------------------------

class ClientMessage : public ::google::protobuf::Message {
 public:
  ClientMessage();
  virtual ~ClientMessage();

  ClientMessage(const ClientMessage& from);

  inline ClientMessage& operator=(const ClientMessage& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ClientMessage& default_instance();

  void Swap(ClientMessage* other);

  // implements Message ----------------------------------------------

  ClientMessage* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ClientMessage& from);
  void MergeFrom(const ClientMessage& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef ClientMessage_AdditioanlRequests AdditioanlRequests;
  static const AdditioanlRequests None = ClientMessage_AdditioanlRequests_None;
  static const AdditioanlRequests FirstConnect = ClientMessage_AdditioanlRequests_FirstConnect;
  static const AdditioanlRequests Reconnect = ClientMessage_AdditioanlRequests_Reconnect;
  static const AdditioanlRequests Disconnect = ClientMessage_AdditioanlRequests_Disconnect;
  static inline bool AdditioanlRequests_IsValid(int value) {
    return ClientMessage_AdditioanlRequests_IsValid(value);
  }
  static const AdditioanlRequests AdditioanlRequests_MIN =
    ClientMessage_AdditioanlRequests_AdditioanlRequests_MIN;
  static const AdditioanlRequests AdditioanlRequests_MAX =
    ClientMessage_AdditioanlRequests_AdditioanlRequests_MAX;
  static const int AdditioanlRequests_ARRAYSIZE =
    ClientMessage_AdditioanlRequests_AdditioanlRequests_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  AdditioanlRequests_descriptor() {
    return ClientMessage_AdditioanlRequests_descriptor();
  }
  static inline const ::std::string& AdditioanlRequests_Name(AdditioanlRequests value) {
    return ClientMessage_AdditioanlRequests_Name(value);
  }
  static inline bool AdditioanlRequests_Parse(const ::std::string& name,
      AdditioanlRequests* value) {
    return ClientMessage_AdditioanlRequests_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // required .ClientMessage.ClientInformation clientinfo = 1;
  inline bool has_clientinfo() const;
  inline void clear_clientinfo();
  static const int kClientinfoFieldNumber = 1;
  inline const ::ClientMessage::ClientInformation& clientinfo() const;
  inline ::ClientMessage::ClientInformation* mutable_clientinfo();
  inline ::ClientMessage::ClientInformation* release_clientinfo();
  inline void set_allocated_clientinfo(::ClientMessage::ClientInformation* clientinfo);

  // required .ClientMessage.Playerinfromation playerinfo = 2;
  inline bool has_playerinfo() const;
  inline void clear_playerinfo();
  static const int kPlayerinfoFieldNumber = 2;
  inline const ::ClientMessage::Playerinfromation& playerinfo() const;
  inline ::ClientMessage::Playerinfromation* mutable_playerinfo();
  inline ::ClientMessage::Playerinfromation* release_playerinfo();
  inline void set_allocated_playerinfo(::ClientMessage::Playerinfromation* playerinfo);

  // required .ClientMessage.ClientMessage.AdditioanlRequests addiontalInfo = 3;
  inline bool has_addiontalinfo() const;
  inline void clear_addiontalinfo();
  static const int kAddiontalInfoFieldNumber = 3;
  inline ::ClientMessage::ClientMessage_AdditioanlRequests addiontalinfo() const;
  inline void set_addiontalinfo(::ClientMessage::ClientMessage_AdditioanlRequests value);

  // @@protoc_insertion_point(class_scope:ClientMessage.ClientMessage)
 private:
  inline void set_has_clientinfo();
  inline void clear_has_clientinfo();
  inline void set_has_playerinfo();
  inline void clear_has_playerinfo();
  inline void set_has_addiontalinfo();
  inline void clear_has_addiontalinfo();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::ClientMessage::ClientInformation* clientinfo_;
  ::ClientMessage::Playerinfromation* playerinfo_;
  int addiontalinfo_;
  friend void  protobuf_AddDesc_ClientMessage_2eproto();
  friend void protobuf_AssignDesc_ClientMessage_2eproto();
  friend void protobuf_ShutdownFile_ClientMessage_2eproto();

  void InitAsDefaultInstance();
  static ClientMessage* default_instance_;
};
// ===================================================================


// ===================================================================

// ClientInformation

// required int32 clientVersion = 1;
inline bool ClientInformation::has_clientversion() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ClientInformation::set_has_clientversion() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ClientInformation::clear_has_clientversion() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ClientInformation::clear_clientversion() {
  clientversion_ = 0;
  clear_has_clientversion();
}
inline ::google::protobuf::int32 ClientInformation::clientversion() const {
  // @@protoc_insertion_point(field_get:ClientMessage.ClientInformation.clientVersion)
  return clientversion_;
}
inline void ClientInformation::set_clientversion(::google::protobuf::int32 value) {
  set_has_clientversion();
  clientversion_ = value;
  // @@protoc_insertion_point(field_set:ClientMessage.ClientInformation.clientVersion)
}

// required int64 messageNumber = 2;
inline bool ClientInformation::has_messagenumber() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ClientInformation::set_has_messagenumber() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ClientInformation::clear_has_messagenumber() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ClientInformation::clear_messagenumber() {
  messagenumber_ = GOOGLE_LONGLONG(0);
  clear_has_messagenumber();
}
inline ::google::protobuf::int64 ClientInformation::messagenumber() const {
  // @@protoc_insertion_point(field_get:ClientMessage.ClientInformation.messageNumber)
  return messagenumber_;
}
inline void ClientInformation::set_messagenumber(::google::protobuf::int64 value) {
  set_has_messagenumber();
  messagenumber_ = value;
  // @@protoc_insertion_point(field_set:ClientMessage.ClientInformation.messageNumber)
}

// -------------------------------------------------------------------

// playerPos

// required float posY = 1;
inline bool playerPos::has_posy() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void playerPos::set_has_posy() {
  _has_bits_[0] |= 0x00000001u;
}
inline void playerPos::clear_has_posy() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void playerPos::clear_posy() {
  posy_ = 0;
  clear_has_posy();
}
inline float playerPos::posy() const {
  // @@protoc_insertion_point(field_get:ClientMessage.playerPos.posY)
  return posy_;
}
inline void playerPos::set_posy(float value) {
  set_has_posy();
  posy_ = value;
  // @@protoc_insertion_point(field_set:ClientMessage.playerPos.posY)
}

// required float posX = 2;
inline bool playerPos::has_posx() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void playerPos::set_has_posx() {
  _has_bits_[0] |= 0x00000002u;
}
inline void playerPos::clear_has_posx() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void playerPos::clear_posx() {
  posx_ = 0;
  clear_has_posx();
}
inline float playerPos::posx() const {
  // @@protoc_insertion_point(field_get:ClientMessage.playerPos.posX)
  return posx_;
}
inline void playerPos::set_posx(float value) {
  set_has_posx();
  posx_ = value;
  // @@protoc_insertion_point(field_set:ClientMessage.playerPos.posX)
}

// -------------------------------------------------------------------

// Playerinfromation

// required int32 playerNumber = 1;
inline bool Playerinfromation::has_playernumber() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Playerinfromation::set_has_playernumber() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Playerinfromation::clear_has_playernumber() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Playerinfromation::clear_playernumber() {
  playernumber_ = 0;
  clear_has_playernumber();
}
inline ::google::protobuf::int32 Playerinfromation::playernumber() const {
  // @@protoc_insertion_point(field_get:ClientMessage.Playerinfromation.playerNumber)
  return playernumber_;
}
inline void Playerinfromation::set_playernumber(::google::protobuf::int32 value) {
  set_has_playernumber();
  playernumber_ = value;
  // @@protoc_insertion_point(field_set:ClientMessage.Playerinfromation.playerNumber)
}

// required .ClientMessage.Playerinfromation.PlayerType type = 2 [default = Unassigned];
inline bool Playerinfromation::has_type() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Playerinfromation::set_has_type() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Playerinfromation::clear_has_type() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Playerinfromation::clear_type() {
  type_ = 3;
  clear_has_type();
}
inline ::ClientMessage::Playerinfromation_PlayerType Playerinfromation::type() const {
  // @@protoc_insertion_point(field_get:ClientMessage.Playerinfromation.type)
  return static_cast< ::ClientMessage::Playerinfromation_PlayerType >(type_);
}
inline void Playerinfromation::set_type(::ClientMessage::Playerinfromation_PlayerType value) {
  assert(::ClientMessage::Playerinfromation_PlayerType_IsValid(value));
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:ClientMessage.Playerinfromation.type)
}

// required .ClientMessage.playerPos pos = 3;
inline bool Playerinfromation::has_pos() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Playerinfromation::set_has_pos() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Playerinfromation::clear_has_pos() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Playerinfromation::clear_pos() {
  if (pos_ != NULL) pos_->::ClientMessage::playerPos::Clear();
  clear_has_pos();
}
inline const ::ClientMessage::playerPos& Playerinfromation::pos() const {
  // @@protoc_insertion_point(field_get:ClientMessage.Playerinfromation.pos)
  return pos_ != NULL ? *pos_ : *default_instance_->pos_;
}
inline ::ClientMessage::playerPos* Playerinfromation::mutable_pos() {
  set_has_pos();
  if (pos_ == NULL) pos_ = new ::ClientMessage::playerPos;
  // @@protoc_insertion_point(field_mutable:ClientMessage.Playerinfromation.pos)
  return pos_;
}
inline ::ClientMessage::playerPos* Playerinfromation::release_pos() {
  clear_has_pos();
  ::ClientMessage::playerPos* temp = pos_;
  pos_ = NULL;
  return temp;
}
inline void Playerinfromation::set_allocated_pos(::ClientMessage::playerPos* pos) {
  delete pos_;
  pos_ = pos;
  if (pos) {
    set_has_pos();
  } else {
    clear_has_pos();
  }
  // @@protoc_insertion_point(field_set_allocated:ClientMessage.Playerinfromation.pos)
}

// -------------------------------------------------------------------

// ClientMessage

// required .ClientMessage.ClientInformation clientinfo = 1;
inline bool ClientMessage::has_clientinfo() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ClientMessage::set_has_clientinfo() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ClientMessage::clear_has_clientinfo() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ClientMessage::clear_clientinfo() {
  if (clientinfo_ != NULL) clientinfo_->::ClientMessage::ClientInformation::Clear();
  clear_has_clientinfo();
}
inline const ::ClientMessage::ClientInformation& ClientMessage::clientinfo() const {
  // @@protoc_insertion_point(field_get:ClientMessage.ClientMessage.clientinfo)
  return clientinfo_ != NULL ? *clientinfo_ : *default_instance_->clientinfo_;
}
inline ::ClientMessage::ClientInformation* ClientMessage::mutable_clientinfo() {
  set_has_clientinfo();
  if (clientinfo_ == NULL) clientinfo_ = new ::ClientMessage::ClientInformation;
  // @@protoc_insertion_point(field_mutable:ClientMessage.ClientMessage.clientinfo)
  return clientinfo_;
}
inline ::ClientMessage::ClientInformation* ClientMessage::release_clientinfo() {
  clear_has_clientinfo();
  ::ClientMessage::ClientInformation* temp = clientinfo_;
  clientinfo_ = NULL;
  return temp;
}
inline void ClientMessage::set_allocated_clientinfo(::ClientMessage::ClientInformation* clientinfo) {
  delete clientinfo_;
  clientinfo_ = clientinfo;
  if (clientinfo) {
    set_has_clientinfo();
  } else {
    clear_has_clientinfo();
  }
  // @@protoc_insertion_point(field_set_allocated:ClientMessage.ClientMessage.clientinfo)
}

// required .ClientMessage.Playerinfromation playerinfo = 2;
inline bool ClientMessage::has_playerinfo() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ClientMessage::set_has_playerinfo() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ClientMessage::clear_has_playerinfo() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ClientMessage::clear_playerinfo() {
  if (playerinfo_ != NULL) playerinfo_->::ClientMessage::Playerinfromation::Clear();
  clear_has_playerinfo();
}
inline const ::ClientMessage::Playerinfromation& ClientMessage::playerinfo() const {
  // @@protoc_insertion_point(field_get:ClientMessage.ClientMessage.playerinfo)
  return playerinfo_ != NULL ? *playerinfo_ : *default_instance_->playerinfo_;
}
inline ::ClientMessage::Playerinfromation* ClientMessage::mutable_playerinfo() {
  set_has_playerinfo();
  if (playerinfo_ == NULL) playerinfo_ = new ::ClientMessage::Playerinfromation;
  // @@protoc_insertion_point(field_mutable:ClientMessage.ClientMessage.playerinfo)
  return playerinfo_;
}
inline ::ClientMessage::Playerinfromation* ClientMessage::release_playerinfo() {
  clear_has_playerinfo();
  ::ClientMessage::Playerinfromation* temp = playerinfo_;
  playerinfo_ = NULL;
  return temp;
}
inline void ClientMessage::set_allocated_playerinfo(::ClientMessage::Playerinfromation* playerinfo) {
  delete playerinfo_;
  playerinfo_ = playerinfo;
  if (playerinfo) {
    set_has_playerinfo();
  } else {
    clear_has_playerinfo();
  }
  // @@protoc_insertion_point(field_set_allocated:ClientMessage.ClientMessage.playerinfo)
}

// required .ClientMessage.ClientMessage.AdditioanlRequests addiontalInfo = 3;
inline bool ClientMessage::has_addiontalinfo() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ClientMessage::set_has_addiontalinfo() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ClientMessage::clear_has_addiontalinfo() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ClientMessage::clear_addiontalinfo() {
  addiontalinfo_ = 1;
  clear_has_addiontalinfo();
}
inline ::ClientMessage::ClientMessage_AdditioanlRequests ClientMessage::addiontalinfo() const {
  // @@protoc_insertion_point(field_get:ClientMessage.ClientMessage.addiontalInfo)
  return static_cast< ::ClientMessage::ClientMessage_AdditioanlRequests >(addiontalinfo_);
}
inline void ClientMessage::set_addiontalinfo(::ClientMessage::ClientMessage_AdditioanlRequests value) {
  assert(::ClientMessage::ClientMessage_AdditioanlRequests_IsValid(value));
  set_has_addiontalinfo();
  addiontalinfo_ = value;
  // @@protoc_insertion_point(field_set:ClientMessage.ClientMessage.addiontalInfo)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ClientMessage

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::ClientMessage::Playerinfromation_PlayerType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::ClientMessage::Playerinfromation_PlayerType>() {
  return ::ClientMessage::Playerinfromation_PlayerType_descriptor();
}
template <> struct is_proto_enum< ::ClientMessage::ClientMessage_AdditioanlRequests> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::ClientMessage::ClientMessage_AdditioanlRequests>() {
  return ::ClientMessage::ClientMessage_AdditioanlRequests_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ClientMessage_2eproto__INCLUDED
