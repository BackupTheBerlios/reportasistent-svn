<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">

  <!-- nastaveni jazyka (defaultne cz) -->
  <xsl:variable name="lng">en</xsl:variable>


  <xsl:template match="/active_list">

    <dialog_data>
      <attributes>
        <attribute name="id" label="id" />

        <xsl:choose>

          <!-- english -->
          <xsl:when test="$lng='en'">
            <attribute name="box_type" label="Box type" />
            <attribute name="user_name" label="User name" />
            <attribute name="user_hint" label="User hint" />
          </xsl:when>

          <!-- cesky-->
          <xsl:when test="$lng='cz'">
            <attribute name="box_type" label="Typ krabičky" />
            <attribute name="user_name" label="Uživatelský název krabičky" />
            <attribute name="user_hint" label="Poznámka" />
          </xsl:when>
        </xsl:choose>

        <!-- vychozi hodnoty:
                numeric_sort="false"
                default_sort_direction="ascending"     -->

      </attributes>

      <values>
        <xsl:apply-templates select="ferda_box" mode="values"/>
      </values>

    </dialog_data>

  </xsl:template>






  <!-- vypise hodnoty -->
<xsl:template match="ferda_box" mode="values">

  <xsl:element name="value">
		<xsl:for-each select="@*">
				<xsl:attribute name="{name()}"><xsl:value-of select="."/></xsl:attribute>
		</xsl:for-each>

  </xsl:element>

</xsl:template>
	



</xsl:stylesheet>
