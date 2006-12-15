<?xml version="1.0" encoding="utf-8"?>

<!-- Sablona vytvori XML soubor "params.xml" s parametry, ktere budeme
     potrebovat pri prevodu asociacniho pravidla. Odkaz na tento soubor
     s parametry se pak předává každé šabloně v každé fázy převodu.         -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

<xsl:include href="config.xsl"/>

<xsl:output indent="yes" method="xml" encoding="utf-8"/>

<xsl:param name="lang"/>
<xsl:param name="rule"/>
<xsl:param name="domain"/>
<xsl:param name="expression"/>


<xsl:template match="/">
  <!-- tisk upozorneni, pokud chyby nejake parametery -->
  <xsl:if test="$lang = ''">
    <xsl:message terminate="yes">Parameter "lang" (language code) is missing</xsl:message>
  </xsl:if>
  <xsl:if test="$rule = ''">
    <xsl:message terminate="yes">Parameter "rule" (hypothesis ID) is missing</xsl:message>
  </xsl:if>
  <xsl:if test="$domain = ''">
    <xsl:message terminate="yes">Parameter "domain" (directory with domain data) is missing</xsl:message>
  </xsl:if>
  <xsl:if test="$expression = ''">
    <xsl:message terminate="yes">Parameter "expression" (directory with elementary expressions) is missing</xsl:message>
  </xsl:if>

  <parameters>
    <param name="fp">
      <xsl:attribute name="value">
        <xsl:text>data/</xsl:text>
        <xsl:value-of select="$lang"/>
	<xsl:text>/fp.xml</xsl:text>
      </xsl:attribute>
    </param>
    <param name="fpa">
      <xsl:attribute name="value">
        <xsl:text>data/</xsl:text>
        <xsl:value-of select="$lang"/>
	<xsl:text>/fpa.xml</xsl:text>
      </xsl:attribute>
    </param>
    <param name="entity">
      <xsl:attribute name="value">
        <xsl:text>data/</xsl:text>
        <xsl:value-of select="$lang"/>
	<xsl:text>/</xsl:text>
	<xsl:value-of select="$domain"/>
	<xsl:text>/entitynames.xml</xsl:text>
      </xsl:attribute>
    </param>
    <param name="elementary">
      <xsl:attribute name="value">
        <xsl:text>data/</xsl:text>
        <xsl:value-of select="$lang"/>
	<xsl:text>/</xsl:text>
	<xsl:value-of select="$domain"/>
	<xsl:text>/</xsl:text>
	<xsl:value-of select="$expression"/>
	<xsl:text>/elementary.xml</xsl:text>
      </xsl:attribute>
    </param>
    <param name="mn">
      <xsl:attribute name="value">
        <xsl:text>data/</xsl:text>
        <xsl:value-of select="$lang"/>
	<xsl:text>/mn.xml</xsl:text>
      </xsl:attribute>
    </param>
    <param name="mv">
      <xsl:attribute name="value">
        <xsl:text>data/</xsl:text>
        <xsl:value-of select="$lang"/>
	<xsl:text>/mv.xml</xsl:text>
      </xsl:attribute>
    </param>
    <param name="langparam">
      <xsl:attribute name="value">
        <xsl:text>data/</xsl:text>
        <xsl:value-of select="$lang"/>
	<xsl:text>/langparam.xml</xsl:text>
      </xsl:attribute>
    </param>
    <param name="rule">
      <xsl:attribute name="value">
        <xsl:text>rules/ar</xsl:text>
        <xsl:value-of select="$rule"/>
	<xsl:text>.xml</xsl:text>
      </xsl:attribute>
    </param>
    <param name="quantifier">
      <xsl:attribute name="value">
        <xsl:value-of select="rule/@quantifier"/>
      </xsl:attribute>
    </param>
    <param name="numofant">
      <xsl:attribute name="value">
        <xsl:value-of select="count(rule/cedent[@type='A']/literal)"/>
      </xsl:attribute>
    </param>
    <param name="numofsuc">
      <xsl:attribute name="value">
        <xsl:value-of select="count(rule/cedent[@type='S']/literal)"/>
      </xsl:attribute>
    </param>

     <param name="numofcon">
      <xsl:attribute name="value">
        <xsl:value-of select="count(rule/cedent[@type='C']/literal)"/>
      </xsl:attribute>
    </param>
	
    <xsl:variable name="_numofant" select="count(rule/cedent[@type='A']/literal)"/>
    <xsl:variable name="_numofsuc" select="count(rule/cedent[@type='S']/literal)"/>
	<xsl:variable name="_numofcon" select="count(rule/cedent[@type='C']/literal)"/>
    
    <xsl:if test="$_numofant = 1">
      <param name="numofantcon">
	<xsl:attribute name="value">1#1+#</xsl:attribute>
      </param>
    </xsl:if>
    <xsl:if test="$_numofant = 2">
      <param name="numofantcon">
	<xsl:attribute name="value">1+#2#2+#</xsl:attribute>
      </param>
    </xsl:if>
    <xsl:if test="$_numofant &gt; 2">
      <param name="numofantcon">
	<xsl:attribute name="value">1+#2+#</xsl:attribute>
      </param>
    </xsl:if>
    
    <xsl:if test="$_numofsuc = 1">
      <param name="numofsuccon">
	<xsl:attribute name="value">1#1+#</xsl:attribute>
      </param>
    </xsl:if>
    <xsl:if test="$_numofsuc = 2">
      <param name="numofsuccon">
	<xsl:attribute name="value">1+#2#2+#</xsl:attribute>
      </param>
    </xsl:if>
    <xsl:if test="$_numofsuc &gt; 2">
      <param name="numofsuccon">
	<xsl:attribute name="value">1+#2+#</xsl:attribute>
      </param>
    </xsl:if>
			  
	<xsl:if test="$_numofcon = 0">
      <param name="numofconcon">
	<xsl:attribute name="value">0#</xsl:attribute>
      </param>
    </xsl:if>
	
	<xsl:if test="$_numofcon = 1">
      <param name="numofconcon">
	<xsl:attribute name="value">1#1+#</xsl:attribute>
      </param>
    </xsl:if>
    <xsl:if test="$_numofcon = 2">
      <param name="numofconcon">
	<xsl:attribute name="value">1+#2#2+#</xsl:attribute>
      </param>
    </xsl:if>
    <xsl:if test="$_numofcon &gt; 2">
      <param name="numofconcon">
	<xsl:attribute name="value">1+#2+#</xsl:attribute>
      </param>
    </xsl:if>

	
  </parameters>

</xsl:template>

</xsl:stylesheet>