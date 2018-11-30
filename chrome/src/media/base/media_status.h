// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_MEDIA_STATUS_H_
#define MEDIA_BASE_MEDIA_STATUS_H_

#include "base/time/time.h"

namespace media {

// Describes the current state of media being controlled via the MediaController
// interface. This is a copy of the media_router.mojom.MediaStatus interface,
// without the cast specific portions.
// TODO(https://crbug.com/820277): Deduplicate media_router::MediaStatus.
struct MediaStatus {
 public:
  enum class PlayState { PLAYING, PAUSED, BUFFERING };

  MediaStatus();
  MediaStatus(const MediaStatus& other);
  ~MediaStatus();

  MediaStatus& operator=(const MediaStatus& other);
  bool operator==(const MediaStatus& other) const;

  // The main title of the media. For example, in a MediaStatus representing
  // a YouTube Cast session, this could be the title of the video.
  std::string title;

  // If this is true, the media can be played and paused.
  bool can_play_pause = false;

  // If this is true, the media can be muted and unmuted.
  bool can_mute = false;

  // If this is true, the media's volume can be changed.
  bool can_set_volume = false;

  // If this is true, the media's current playback position can be changed.
  bool can_seek = false;

  PlayState play_state = PlayState::PLAYING;

  bool is_muted = false;

  // Current volume of the media, with 1 being the highest and 0 being the
  // lowest/no sound. When |is_muted| is true, there should be no sound
  // regardless of |volume|.
  float volume = 0;

  // The length of the media. A value of zero indicates that this is a media
  // with no set duration (e.g. a live stream).
  base::TimeDelta duration;

  // Current playback position. Must be less than or equal to |duration|.
  base::TimeDelta current_time;
};

}  // namespace media

#endif  // MEDIA_BASE_MEDIA_STATUS_H_