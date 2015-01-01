# topicsview.coffee
# 8/29/2014 jichi
# Required by chat.haml
#
# Beans:
# - cacheBean: cacheman.CacheCoffeeBean
# - i18nBean: coffeebean.I18nBean
# - mainBean: coffeebean.MainBean
# - postInputBean: postinput.PostInputManagerBean
# - postEditBean: postedit.PostEditorManagerBean

dprint = ->
  Array::unshift.call arguments, 'topicsview:'
  console.log.apply console, arguments

# Global variables
@READY = false # needed by chatview.py

newTopic = (subjectId) -> topicInputBean.newTopic subjectId # long ->
newPost = (topicId) -> postInputBean.newPost topicId # long ->

# Export functions

@spin = (t) -> # bool ->
  if t
    @spin.count += 1
  else
    @spin.count -= 1
  $('#spin').spin if @spin.count > 0 then 'large' else false
@spin.count = 0

@addTopic = (topic) ->
  if READY
    if topic.type is 'review'
      @reviewView?.addTopic topic
    else
      @topicView?.addTopic topic
@updateTopic = (topic) ->
  if READY
    if topic.type is 'review'
      @reviewView?.updateTopic topic
    else
      @topicView?.updateTopic topic

@addPost = (post) -> @chatView?.addPost post if READY
@updatePost = (post) -> @chatView?.updatePost post if READY

# Init

createObjects = ->
  # Reviews
  $sec = $ '.sec-reviews'
  search =
    type: 'review'
  subjectId = $sec.data 'subject-id'
  if subjectId
    search.subjectId = subjectId
    search.subjectType = 'game'
  @reviewView = new topicsjs.TopicList
    container: $sec.find '> .sec-content > .forum-topics'
    more: $sec.find '> .sec-content > .footer'
    search: search

  # Topics
  $sec = $ '.sec-topics'
  search =
    notype: 'review'
  subjectId = $sec.data 'subject-id'
  if subjectId
    search.subjectId = subjectId
    search.subjectType = $sec.data 'subject-type'
  @topicView = new topicsjs.TopicList
    container: $sec.find '> .sec-content > .forum-topics'
    more: $sec.find '> .sec-content > .footer'
    search: search

  # Posts
  $sec = $ '.sec-chat'
  topicId = $sec.data 'topic-id'
  if topicId
    @chatView = new postsjs.PostList
      container: $sec.find '> .sec-content > .forum-posts'
      more: $sec.find '> .sec-content > .footer'
      topicId: topicId

bind = ->
  $('.sec-btn').click ->
    $this = $ @
    $sec = $this.parent '.sec'
    if $sec.length
      $target = $sec.find '.sec-content'
      unless $target.is(':empty') and $this.hasClass('checked')
        $this.toggleClass 'checked'
        #effect = $this.data('effect') or 'blind'
        #effect = $this.data('effect') or 'fade'
        #$target.toggle effect unless $target.is ':empty'
        $target.toggle 'fade' unless $target.is ':empty'
    false

  # Chat
  $sec = $('.sec.sec-topic')
  $sec.find('.new-topic').click ->
    subjectId = $(@).parent().data 'subject-id'
    newTopic subjectId
    false

  $sec = $('.sec.sec-chat')
  $sec.find('.new-chat').click ->
    topicId = $(@).parent().data 'topic-id'
    newPost topicId
    false

init = ->
  unless @i18nBean? # the last injected bean
    dprint 'init: wait'
    setTimeout init, 100 # Wait until bean is ready
  else
    dprint 'init: enter'

    moment.locale 'ja'

    topicsjs.init()
    postsjs.init()

    createObjects()

    bind()

    @READY = true

    #setTimeout gm.show, 200
    #setTimeout _.partial(quicksearch, styleClass, gf.refreshFilter),  2000
    dprint 'init: leave'

$ -> init()

# EOF
