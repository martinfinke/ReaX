#pragma once

/**
 Adds reactive extensions to a `juce::Value`.
 
 Instead of creating a `juce::Value`, create an instance of this as follows:
 
     Reactive<juce::Value> myValue;
 
 It's implicitly convertible from and to `juce::Value`. And you can access `myValue.rx.subject` to subscribe to changes, etc.:
 
     myValue.rx.subject.map(...).filter(...).subscribe(...);
 
 You can subscribe this value to some `Observable<var>`, to change the value whenever the Observable emits a value:
 
     someObservable.subscribe(myValue.rx.subject);
 */
template<>
class Reactive<juce::Value>
{
public:
    /// Creates a new instance. Has the same behavior as the `juce::Value` equivalent.
    ///@{
    Reactive();
    Reactive(const juce::Value& other);
    explicit Reactive(const juce::var& initialValue);
    ///@}

    /// Converts the `Reactive<juce::Value>` to a `juce::Value`.
    operator juce::Value() const;

    /// Returns the current value.
    juce::var getValue() const;

    /// Returns the current value.
    operator juce::var() const;

    /// Sets a new value.
    void setValue(const juce::var& newValue);

    /// Sets a new value. This is the same as calling `setValue`.
    Reactive<juce::Value>& operator=(const juce::var& newValue);
    
    /// Makes this object refer to the same ValueSource as another one.
    void referTo(const juce::Value& valueToReferTo);
    
    /// Same as referTo(newValue).
    Reactive<juce::Value>& operator=(const juce::Value& newValue);

    /// The reactive extension object.
    ValueExtension rx;

private:
    Reactive<juce::Value>& operator=(const Reactive<juce::Value>&) = delete;
};

/**
 Adds reactive extensions to an `AudioProcessor`.
 */
template<>
class Reactive<juce::AudioProcessor> : public juce::AudioProcessor
{
public:
    /// Creates a new instance. @see `juce::AudioProcessor::AudioProcessor`.
    template<typename... Args>
    Reactive(Args&&... args)
    : juce::AudioProcessor(std::forward<Args>(args)...),
      rx(*this)
    {}

    /// The reactive extension object.
    const AudioProcessorExtension rx;
};


/**
 Adds reactive extensions to an `AudioProcessorValueTreeState`.
 */
template<>
class Reactive<juce::AudioProcessorValueTreeState> : public juce::AudioProcessorValueTreeState
{
public:
    /// Creates a new instance. @see `juce::AudioProcessorValueTreeState::AudioProcessorValueTreeState`.
    Reactive(juce::AudioProcessor& processorToConnectTo, juce::UndoManager* undoManagerToUse);

    /// The reactive extension object.
    const AudioProcessorValueTreeStateExtension rx;
};
